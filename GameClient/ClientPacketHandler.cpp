#include "pch.h"
#include "ClientPacketHandler.h"

bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
    return false;
}

void ClientPacketHandler::Init()
{
    // ��Ŷ ID�� �ڵ鷯�� ���� (���� �� Ŭ���̾�Ʈ ���� ��Ŷ)
    RegisterPacketHandler<Protocol::LoginResponse>(PacketID::LOGIN_RESPONSE, Handle_LoginResponse);
    RegisterPacketHandler<Protocol::EnterGameResponse>(PacketID::ENTER_GAME_RESPONSE, Handle_EnterGameResponse);
    RegisterPacketHandler<Protocol::PlayerMoveResponse>(PacketID::PLAYER_MOVE_RESPONSE, Handle_PlayerMoveResponse);
    RegisterPacketHandler<Protocol::ChatResponse>(PacketID::CHAT_RESPONSE, Handle_ChatResponse);
    RegisterPacketHandler<Protocol::ActionResponse>(PacketID::ACTION_RESPONSE, Handle_ActionResponse);
    RegisterPacketHandler<Protocol::ActionResponse>(PacketID::WORLD_STATE_UPDATE, Handle_WorldStateUpdate);
}

bool ClientPacketHandler::Handle_LoginResponse(shared_ptr<PacketSession>& session, Protocol::LoginResponse& packet)
{
    if (packet.success()) {
        // 1. �α��� ���� ó��
        printf("Login successful! Welcome to the game.\n");

        // �� ��ȯ or �κ� �̵�
        //GameSceneManager::LoadScene("LobbyScene");
    }
    else {
        // 2. �α��� ���� ó��
        printf("Login failed: %s\n", packet.error_message().c_str());

        // ���� �޽����� UI �˾����� ǥ��
        //GameUI::ShowErrorPopup(packet.error_message());
    }

    return true;
}

bool ClientPacketHandler::Handle_EnterGameResponse(shared_ptr<PacketSession>& session, Protocol::EnterGameResponse& packet)
{
    printf("Entered game world. Welcome!\n");
    return true;
}

bool ClientPacketHandler::Handle_PlayerMoveResponse(shared_ptr<PacketSession>& session, Protocol::PlayerMoveResponse& packet)
{
    printf("Player move acknowledged.\n");
    return true;
}

bool ClientPacketHandler::Handle_ChatResponse(shared_ptr<PacketSession>& session, Protocol::ChatResponse& packet)
{
    return true;
}

bool ClientPacketHandler::Handle_ActionResponse(shared_ptr<PacketSession>& session, Protocol::ActionResponse& packet)
{
    printf("Action response received.\n");
    return true;
}

bool ClientPacketHandler::Handle_WorldStateUpdate(shared_ptr<PacketSession>& session, Protocol::ActionResponse& packet)
{
    printf("World state updated.\n");
    return true;
}
