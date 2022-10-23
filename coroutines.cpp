#include<iostream> // std::cout
#include<string> // std::string
#include<coroutine> // std::suspend always, std::coroutine_handle
#include<utility> // std::exchange

struct promise_type;

struct Chat
{
    using handle = std::coroutine_handle<promise_type>;
    handle coroutine_handle{};

    explicit Chat(promise_type* p) : coroutine_handle(handle::from_promise(*p)) {}
    Chat(Chat&& rhs) : coroutine_handle{std::exchange(rhs.coroutine_handle, nullptr)} {}

    ~Chat()
    {
        if(coroutine_handle) {coroutine_handle.destroy();}
    }

    std::string listen()
    {
        if(not coroutine_handle.done()) {coroutine_handle.resume();}
        return std::move(coroutine_handle.promise().message_out);
    }

    void answer(std::string msg)
    {
        coroutine_handle.promise().message_in = msg;
        if(not coroutine_handle.done()) {coroutine_handle.resume();}
    } 
};

struct promise_type
{
    std::string message_out{};
    std::string message_in{};

    void unhandled_exception() noexcept {}
    Chat get_return_object() {return Chat(this);}
    std::suspend_always initial_suspend() noexcept {return {};}
    std::suspend_always yield_value(std::string msg) noexcept
    {
        message_out = std::move(msg);
        return {};
    }
    auto await_transform(std::string) noexcept
    {
        struct awaiter
        {
            promise_type& pt;
            constexpr bool await_ready() const noexcept {return true;}
            std::string await_resume() const noexcept {return std::move(pt.message_in);}
            void await_suspend(std::coroutine_handle<>) const noexcept {}
        };

        return awaiter(*this);
    }
    void return_value(std::string msg) noexcept {message_out = std::move(msg);}
    std::suspend_always final_suspend() noexcept {return {};}
};

Chat Fun()
{
    co_yield std::string("Hello!\n");
    std::cout << co_await std::string{};
    co_return "Here!\n";
}

void use()
{
    Chat chat = Fun();
    std::cout << chat.listen();
    chat.answer("Where are you?\n");
    std::cout << chat.listen();
}
