/*******************************************************************************
 * Project:  AccessServer
 * @file     CmdToClient.cpp
 * @brief 
 * @author   Bwar
 * @date:    2015年10月20日
 * @note
 * Modify history:
 ******************************************************************************/
#include "CmdToClient.hpp"
#include <actor/step/Step.hpp>


namespace acc
{

CmdToClient::CmdToClient(int32 iCmd)
    : neb::Cmd(iCmd)
{
}

CmdToClient::~CmdToClient()
{
}

bool CmdToClient::AnyMessage(std::shared_ptr<neb::SocketChannel> pChannel,
    const MsgHead& oMsgHead, const MsgBody& oMsgBody)
{
    auto pStepToClient = MakeSharedStep("acc::StepToClient", pChannel, oMsgHead, oMsgBody);
    if (pStepToClient == nullptr)
    {
        LOG4_ERROR("error %d: new StepFromClient() error!", neb::ERR_NEW);
        return(false);
    }
    pStepToClient->Emit();
    return(true);
}

} /* namespace acc */

