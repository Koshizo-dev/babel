#pragma once

#include "Message.hpp"
#include "Client.hpp"

#include <string>
#include <variant>
#include <iostream>

namespace babel {

    class Event {
        public:
            enum EventType {
                LOGIN_FAILED,
                LOGOUT,
                CONTACT_FILTER_UPDATE,
                NEW_CONTACT,
                NEW_BULK_CONTACT,
                NEW_MESSAGE,
                NEW_BULK_MESSAGE,
                NEW_CLIENT,
                NEW_CHATTING,
                CALL_STATE_UPDATE,
            };
    
            struct LoginFailed {
                std::string errorMessage;
            } loginFailed;

            struct ContactFilterUpdate {
                std::string filter;
            } contactFilter;

            struct NewContact {
                std::shared_ptr<Client> contact;
            } newContact;

            struct NewBulkContact {
                std::vector<std::shared_ptr<Client>> contacts;
            } newBulkContact;

            struct NewMessage {
                std::shared_ptr<Message> message;
            } newMessage;

            struct NewBulkMessage {
                std::vector<std::shared_ptr<Message>> messages;
            } newBulkMessage;

            struct NewClient {
                std::shared_ptr<Client> client;
            } newClient;

            struct NewChatting {
                std::shared_ptr<Client> previousClient;
                std::shared_ptr<Client> newClient;
            } newChatting;

            struct CallStateUpdate {
                std::shared_ptr<Client> update;
            } callStateUpdate;

            union Data {

                LoginFailed loginFailed;
                ContactFilterUpdate contactFilter;
                NewContact newContact;
                NewBulkContact newBulkContact;
                NewMessage newMessage;
                NewBulkMessage newBulkMessage;
                NewClient newClient;
                NewChatting newChatting;
                CallStateUpdate callStateUpdate;

                Data() {}
                ~Data() {}
        
            };

            Event(EventType type) : type(type) {}

            Data data;
            EventType type;
    };
}
