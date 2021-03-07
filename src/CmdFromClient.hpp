/*******************************************************************************
 * Project:  AccessServer
 * @file     CmdFromClient.hpp
 * @brief 
 * @author   Bwar
 * @date:    2015年10月21日
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_CMDFROMCLIENT_CMDFROMCLIENT_HPP_
#define SRC_CMDFROMCLIENT_CMDFROMCLIENT_HPP_

#include <actor/cmd/Cmd.hpp>
#include <actor/DynamicCreator.hpp>

namespace acc
{

class CmdFromClient: public neb::Cmd,
    public neb::DynamicCreator<CmdFromClient, int32>
{
public:
    CmdFromClient(int32 iCmd);
    virtual ~CmdFromClient();
    virtual bool AnyMessage(
            std::shared_ptr<neb::SocketChannel> pChannel,
            const MsgHead& oMsgHead,
            const MsgBody& oMsgBody);
};

} /* namespace acc */

#endif /* SRC_CMDFROMCLIENT_CMDFROMCLIENT_HPP_ */

