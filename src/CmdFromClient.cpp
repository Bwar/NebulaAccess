/*******************************************************************************
 * Project:  AccessServer
 * @file     CmdFromClient.cpp
 * @brief 
 * @author   Bwar
 * @date:    2015年10月21日
 * @note
 * Modify history:
 ******************************************************************************/
#include "CmdFromClient.hpp"
#include <actor/step/Step.hpp>

namespace acc
{

CmdFromClient::CmdFromClient(int32 iCmd)
    : neb::Cmd(iCmd)
{
}

CmdFromClient::~CmdFromClient()
{
}

bool CmdFromClient::AnyMessage(std::shared_ptr<neb::SocketChannel> pChannel,
        const MsgHead& oMsgHead, const MsgBody& oMsgBody)
{
    auto pStepFromClient = MakeSharedStep("acc::StepFromClient", pChannel, oMsgHead, oMsgBody);
    if (pStepFromClient == nullptr)
    {
        LOG4_ERROR("error %d: new StepFromClient() error!", neb::ERR_NEW);
        return(false);
    }
    pStepFromClient->Emit();
    return(true);
}

} /* namespace acc */

