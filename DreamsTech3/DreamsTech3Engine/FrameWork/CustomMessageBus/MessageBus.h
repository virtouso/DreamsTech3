#include <functional>
#include <queue>
#include <vector>




class MessageBus
{
public:
    MessageBus() {};
    ~MessageBus() {};

    void addReceiver(std::function<void(Message)> messageReceiver)
    {
        receivers.push_back(messageReceiver);
    }

    void sendMessage(Message message)
    {
        messages.push(message);
    }

    void notify()
    {
        while (!messages.empty()) {
            for (auto iter = receivers.begin(); iter != receivers.end(); iter++) {
                (*iter)(messages.front());
            }

            messages.pop();
        }
    }

private:
    std::vector<std::function<void(Message)>> receivers;
    std::queue<Message> messages;
};