/*******************************************************************************
 * Project:  AccessServer
 * @file     StepFromClient.cpp
 * @brief 
 * @author   Bwar
 * @date:    2015年10月21日
 * @note
 * Modify history:
 ******************************************************************************/
#include "StepFromClient.hpp"

namespace acc
{

StepFromClient::StepFromClient(std::shared_ptr<neb::SocketChannel> pChannel,
        const MsgHead& oMsgHead, const MsgBody& oMsgBody)
    : m_pChannel(pChannel), m_oMsgHead(oMsgHead), m_oMsgBody(oMsgBody)
{
}

StepFromClient::~StepFromClient()
{
}

neb::E_CMD_STATUS StepFromClient::Emit(int iErrno, const std::string& strErrMsg, void* data)
{
    if (SendOriented("LOGIC", m_oMsgHead.cmd(), GetSequence(), m_oMsgBody))
    {
        return(neb::CMD_STATUS_RUNNING);
    }
    return(neb::CMD_STATUS_FAULT);
}

neb::E_CMD_STATUS StepFromClient::Callback(
        std::shared_ptr<neb::SocketChannel> pChannel,
        const MsgHead& oMsgHead, const MsgBody& oMsgBody, void* data)
{
    SendTo(m_pChannel, oMsgHead.cmd(), m_oMsgHead.seq(), oMsgBody);
    return(neb::CMD_STATUS_COMPLETED);
}

neb::E_CMD_STATUS StepFromClient::ErrBack(std::shared_ptr<neb::SocketChannel> pChannel,
            int iErrno, const std::string& strErrMsg)
{
    MsgBody oOutMsgBody;
    oOutMsgBody.mutable_rsp_result()->set_code(iErrno);
    oOutMsgBody.mutable_rsp_result()->set_msg(strErrMsg);
    SendTo(m_pChannel, m_oMsgHead.cmd() + 1, m_oMsgHead.seq(), oOutMsgBody);
    return(neb::CMD_STATUS_FAULT);
}

neb::E_CMD_STATUS StepFromClient::Timeout()
{
    LOG4_WARNING("cmd %u, seq %lu, logic timeout!", m_oMsgHead.cmd(), m_oMsgHead.seq());
    return(neb::CMD_STATUS_FAULT);
}

} /* namespace acc */

