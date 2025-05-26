#include "pch.h"
#include "ServerPacketHandler.h"


bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
    return false;
}


// ��Ŷ �ڵ鷯 �ʱ�ȭ (���� ���� �� 1ȸ ȣ��)
void ServerPacketHandler::Init()
{
    // ��û ��Ŷ�� ���� �ڵ鷯 ���
    RegisterPacketHandler<Protocol::LoginRequest>(PacketID::LOGIN_REQUEST, Handle_LoginRequest);
    RegisterPacketHandler<Protocol::EnterGameRequest>(PacketID::ENTER_GAME_REQUEST, Handle_EnterGameRequest);
    RegisterPacketHandler<Protocol::PlayerMoveRequest>(PacketID::PLAYER_MOVE_REQUEST, Handle_PlayerMoveRequest);
    RegisterPacketHandler<Protocol::ChatRequest>(PacketID::CHAT_REQUEST, Handle_ChatRequest);
    RegisterPacketHandler<Protocol::ActionRequest>(PacketID::ACTION_REQUEST, Handle_ActionRequest);
}

bool ServerPacketHandler::Handle_LoginRequest(shared_ptr<PacketSession>& session, Protocol::LoginRequest& packet)
{
    printf("Login request from: %s\n", packet.userid().c_str());

    Protocol::LoginResponse response;

    // 1. �ӽ� ��ū ���� (�ϵ��ڵ��� ��ū ���)
    const std::string validToken = "debug-token-12345";

    if (packet.token() != validToken) {
        // 2. ���� ó��
        response.set_success(false);
        response.set_errormessage("Invalid token");
        printf("Login failed for %s - Invalid token\n", packet.userid().c_str());
    }
    else {
        // 3. ���� ó��
        response.set_success(true);
        printf("Login successful for %s\n", packet.userid().c_str());
    }

    // 5. ���� ����
    auto sendBuffer = MakeSendBuffer(response);
    session->Send(sendBuffer);

    return response.success();
}



// ���� ���� ��û
bool ServerPacketHandler::Handle_EnterGameRequest(shared_ptr<PacketSession>& session, Protocol::EnterGameRequest& packet)
{

    return true;
}

// �÷��̾� �̵� ��û ó��
bool ServerPacketHandler::Handle_PlayerMoveRequest(shared_ptr<PacketSession>& session, Protocol::PlayerMoveRequest& packet)
{

    return true;
}

// ä�� ��û ó��
bool ServerPacketHandler::Handle_ChatRequest(shared_ptr<PacketSession>& session, Protocol::ChatRequest& packet)
{

    return true;
}

// �׼� ��û ó��
bool ServerPacketHandler::Handle_ActionRequest(shared_ptr<PacketSession>& session, Protocol::ActionRequest& packet)
{

    return true;
}
