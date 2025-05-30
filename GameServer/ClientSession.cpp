#include "pch.h"
#include "ClientSession.h"
#include "SessionManager.h"

#include "ServerPacketHandler.h"

void ClientSession::OnConnected()
{
    SessionManager::Get().Add(GetClientSession());
	printf("클라이언트 연결 됨\n");
}

int ClientSession::OnRecvPacket(BYTE* buffer, int len)
{
    shared_ptr<PacketSession> session = GetPacketSession();
    ServerPacketHandler::HandlePacket(session, buffer, len);

    return len;
}

void ClientSession::OnSend(int len)
{
}

void ClientSession::OnDisconnected()
{
    SessionManager::Get().Remove(GetClientSession());
}