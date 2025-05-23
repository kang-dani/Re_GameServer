#pragma once
#include "pch.h"
#include <ClientService.h>
#include "ServerSession.h"
#include "ClientPacketHandler.h"
#include <thread>
#include <chrono>

int main()
{
    ClientPacketHandler::Init();

    std::this_thread::sleep_for(1s);

    printf("============== Client  ================\n");
     shared_ptr<ClientService> clientService = make_shared<ClientService>(L"127.0.0.1", 27015, []() {return make_shared<ServerSession>(); });

     //1000�� ���� ���� ����
     for (int i = 0; i < 1; i++)
     {
         if (!clientService->Start())
         {
             printf("Can not Start\n");
             return 1;

         }
     }

    thread t
    (
        [=]()
        {
            while (true)
            {
                clientService->ObserveIO();
            }
        }
    );


    while (true)
    {
    }

    t.join();

    return 0;
}
