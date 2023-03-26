#pragma once

#include "Client.hpp"
#include "audio/AudioSettings.hpp"
#include "audio/AudioSocket.hpp"
#include "scenes/SceneManager.hpp"
#include "../protocol/PacketManager.hpp"
#include "EventManager.hpp"
#include "network/Transporter.hpp"
#include "audio/Audio.hpp"

#include <mutex>
#include <vector>
#include <thread>

namespace babel {

    class ClientManager {
        public:
            std::mutex mutex;

            const std::shared_ptr<Client> getClient(std::string username) const;
            const std::shared_ptr<Client> getChatting() const;
            const void reset();
            const void disconnect();
            const void startAudioSocket();
            const void stopAudioSocket();

            std::shared_ptr<SceneManager> sceneManager = nullptr;
            std::shared_ptr<Audio> audioDevice = nullptr;
            std::vector<std::shared_ptr<Client>> clients = {};
            std::shared_ptr<EventManager> eventManager = nullptr;
            std::shared_ptr<PacketManager> packetManager = nullptr;
            std::shared_ptr<Client> self = nullptr;
            std::shared_ptr<Transporter> transporter = nullptr;
            std::shared_ptr<AudioSettings> audioSettings = nullptr;
            std::shared_ptr<AudioSocket> audioSocket = nullptr;

        private:
            std::mutex _audioMutex;
            bool _isAudioSocketRunning = false;

            std::thread *_audioThread = nullptr;

            const void _initAudioSocket();
    };
}