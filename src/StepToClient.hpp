/*******************************************************************************
 * Project:  AccessServer
 * @file     StepToClient.hpp
 * @brief 
 * @author   Bwar
 * @date:    2015年10月21日
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_CMDTOCLIENT_STEPTOCLIENT_HPP_
#define SRC_CMDTOCLIENT_STEPTOCLIENT_HPP_

#include <actor/step/PbStep.hpp>

namespace acc
{

class StepToClient: public neb::PbStep,
    public neb::DynamicCreator<StepToClient,
        std::shared_ptr<neb::SocketChannel>&, const MsgHead&, const MsgBody&>
{
public:
    StepToClient(std::shared_ptr<neb::SocketChannel> pChannel,
            const MsgHead& oMsgHead, const MsgBody& oMsgBody);
    virtual ~StepToClient();

    virtual neb::E_CMD_STATUS Emit(int iErrno = neb::ERR_OK, const std::string& strErrMsg = "", void* data = NULL);
    virtual neb::E_CMD_STATUS Callback(
            std::shared_ptr<neb::SocketChannel> pChannel,
            const MsgHead& oMsgHead, const MsgBody& oMsgBody, void* data = NULL);
    virtual neb::E_CMD_STATUS ErrBack(std::shared_ptr<neb::SocketChannel> pChannel,
            int iErrno, const std::string& strErrMsg);
    virtual neb::E_CMD_STATUS Timeout();

private:
    std::shared_ptr<neb::SocketChannel> m_pChannel;
    MsgHead m_oMsgHead;
    MsgBody m_oMsgBody;
};

} /* namespace acc */

#endif /* SRC_CMDTOCLIENT_STEPTOCLIENT_HPP_ */

