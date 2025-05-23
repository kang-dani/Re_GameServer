#pragma once
#include <PacketHandler.h>
#include "Protocol.pb.h"  // Protobuf���� ������ ��� ����

// ��Ŷ ID ����
enum class PacketID : uint16
{
    // Ŭ���̾�Ʈ �� ���� ��Ŷ
    LOGIN_REQUEST = 1001,
    ENTER_GAME_REQUEST = 1101,
    PLAYER_MOVE_REQUEST = 1201,
    CHAT_REQUEST = 1301,
    ACTION_REQUEST = 1401,

    // ���� �� Ŭ���̾�Ʈ ���� ��Ŷ
    LOGIN_RESPONSE = 1002,
    ENTER_GAME_RESPONSE = 1102,
    PLAYER_MOVE_RESPONSE = 1202,
    CHAT_RESPONSE = 1302,
    ACTION_RESPONSE = 1402,
    WORLD_STATE_UPDATE = 1501
};

// ���� ��Ŷ �ڵ鷯 ����
class ServerPacketHandler : public PacketHandler
{
public:
    // �ʱ�ȭ (��Ŷ �ڵ鷯 ���)
    static void Init();

    // Ŭ���̾�Ʈ �� ���� ��û ó�� �ڵ鷯
    static bool Handle_LoginRequest(shared_ptr<PacketSession>& session, Protocol::LoginRequest& packet);
    static bool Handle_EnterGameRequest(shared_ptr<PacketSession>& session, Protocol::EnterGameRequest& packet);
    static bool Handle_PlayerMoveRequest(shared_ptr<PacketSession>& session, Protocol::PlayerMoveRequest& packet);
    static bool Handle_ChatRequest(shared_ptr<PacketSession>& session, Protocol::ChatRequest& packet);
    static bool Handle_ActionRequest(shared_ptr<PacketSession>& session, Protocol::ActionRequest& packet);

    // ���� �� Ŭ���̾�Ʈ ���� ����
    static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::LoginResponse& packet)
    {
        return MakeSendBuffer(packet, PacketID::LOGIN_RESPONSE);
    }

    static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::EnterGameResponse& packet)
    {
        return MakeSendBuffer(packet, PacketID::ENTER_GAME_RESPONSE);
    }

    static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::PlayerMoveResponse& packet)
    {
        return MakeSendBuffer(packet, PacketID::PLAYER_MOVE_RESPONSE);
    }

    static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::ChatResponse& packet)
    {
        return MakeSendBuffer(packet, PacketID::CHAT_RESPONSE);
    }

    static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::ActionResponse& packet)
    {
        return MakeSendBuffer(packet, PacketID::ACTION_RESPONSE);
    }

protected:
    template<typename T>
    static shared_ptr<SendBuffer> MakeSendBuffer(T& packet, PacketID packetId)
    {
        // enum class -> uint16 ��ȯ �� protected ȣ��
        return PacketHandler::MakeSendBuffer(packet, static_cast<uint16_t>(packetId));
    }

    template<typename PacketType, typename Handler>
    static void RegisterPacketHandler(PacketID packetId, Handler handler)
    {
        PacketHandler::RegisterPacketHandler<PacketType>(static_cast<uint16_t>(packetId), handler);
    }
};
