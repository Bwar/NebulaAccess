/*******************************************************************************
 * Project:  AccessServer
 * @file     StepToClient.cpp
 * @brief 
 * @author   Bwar
 * @date:    2015年10月21日
 * @note
 * Modify history:
 ******************************************************************************/
#include "StepToClient.hpp"

namespace acc
{

StepToClient::StepToClient(std::shared_ptr<neb::SocketChannel> pChannel,
        const MsgHead& oMsgHead, const MsgBody& oMsgBody)
    : m_pChannel(pChannel), m_oMsgHead(oMsgHead), m_oMsgBody(oMsgBody)
{
}

StepToClient::~StepToClient()
{
}

neb::E_CMD_STATUS StepToClient::Emit(int iErrno, const std::string& strErrMsg, void* data)
{
    MsgBody oOutMsgBody;
    if (m_oMsgBody.has_req_target())
    {
        if (0 != m_oMsgBody.req_target().route_id())
        {
            if(SendTo(std::to_string(m_oMsgBody.req_target().route_id()),
                    m_oMsgHead.cmd(), GetSequence(), m_oMsgBody, neb::CODEC_PROTO))
            {
                return(neb::CMD_STATUS_RUNNING);
            }
            else
            {
                oOutMsgBody.mutable_rsp_result()->set_code(neb::ERR_SESSION);
                oOutMsgBody.mutable_rsp_result()->set_msg("send to "
                        + std::to_string(m_oMsgBody.req_target().route_id()) + "failed.");
                SendTo(m_pChannel, m_oMsgHead.cmd() + 1, m_oMsgHead.seq(), oOutMsgBody);
                return(neb::CMD_STATUS_FAULT);
            }
        }
        else if (m_oMsgBody.req_target().route().length() > 0)
        {
            if(SendTo(m_oMsgBody.req_target().route(),
                    m_oMsgHead.cmd(), GetSequence(), m_oMsgBody, neb::CODEC_PROTO))
            {
                return(neb::CMD_STATUS_RUNNING);
            }
            else
            {
                oOutMsgBody.mutable_rsp_result()->set_code(neb::ERR_SESSION);
                oOutMsgBody.mutable_rsp_result()->set_msg("send to "
                        + m_oMsgBody.req_target().route() + "failed.");
                SendTo(m_pChannel, m_oMsgHead.cmd() + 1, m_oMsgHead.seq(), oOutMsgBody);
                return(neb::CMD_STATUS_FAULT);
            }
        }
        else
        {
            oOutMsgBody.mutable_rsp_result()->set_code(neb::ERR_SESSION);
            oOutMsgBody.mutable_rsp_result()->set_msg("missing MsgBody.req_target.route_id or "
                    "MsgBody.req_target.route.");
            SendTo(m_pChannel, m_oMsgHead.cmd() + 1, m_oMsgHead.seq(), oOutMsgBody);
            return(neb::CMD_STATUS_FAULT);
        }
    }
    oOutMsgBody.mutable_rsp_result()->set_code(neb::ERR_SESSION);
    oOutMsgBody.mutable_rsp_result()->set_msg("missing MsgBody.req_target.");
    SendTo(m_pChannel, m_oMsgHead.cmd() + 1, m_oMsgHead.seq(), oOutMsgBody);
    return(neb::CMD_STATUS_FAULT);
}

neb::E_CMD_STATUS StepToClient::Callback(
        std::shared_ptr<neb::SocketChannel> pChannel,
        const MsgHead& oMsgHead, const MsgBody& oMsgBody, void* data)
{
    SendTo(m_pChannel, oMsgHead.cmd(), m_oMsgHead.seq(), oMsgBody);
    return(neb::CMD_STATUS_COMPLETED);
}

neb::E_CMD_STATUS StepToClient::ErrBack(std::shared_ptr<neb::SocketChannel> pChannel,
            int iErrno, const std::string& strErrMsg)
{
    MsgBody oOutMsgBody;
    oOutMsgBody.mutable_rsp_result()->set_code(iErrno);
    oOutMsgBody.mutable_rsp_result()->set_msg(strErrMsg);
    SendTo(m_pChannel, m_oMsgHead.cmd() + 1, m_oMsgHead.seq(), oOutMsgBody);
    return(neb::CMD_STATUS_FAULT);
}

neb::E_CMD_STATUS StepToClient::Timeout()
{
    LOG4_WARNING("cmd %u, seq %lu, logic timeout!", m_oMsgHead.cmd(), m_oMsgHead.seq());
    return(neb::CMD_STATUS_FAULT);
}

} /* namespace acc */


