/*******************************************************************************
 * Project:  AccessServer
 * @file     CmdToClient.hpp
 * @brief 
 * @author   Bwar
 * @date:    2015年10月20日
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_CMDTOCLIENT_CMDTOCLIENT_HPP_
#define SRC_CMDTOCLIENT_CMDTOCLIENT_HPP_

#include <actor/cmd/Cmd.hpp>
#include <actor/DynamicCreator.hpp>

namespace acc
{

class CmdToClient: public neb::Cmd,
    public neb::DynamicCreator<CmdToClient, int32>
{
public:
    CmdToClient(int32 iCmd);
    virtual ~CmdToClient();
    virtual bool AnyMessage(
            std::shared_ptr<neb::SocketChannel> pChannel,
            const MsgHead& oMsgHead,
            const MsgBody& oMsgBody);
};

} /* namespace acc */

#endif /* SRC_CMDTOCLIENT_CMDTOCLIENT_HPP_ */

