#include <iostream>

#include <fabulist/speaker.hpp>
#include <fabulist/story.hpp>

#include <sol/sol.hpp>

#include <story_impl.hpp>

using namespace fabulist;

sol::function options(const std::string& option, sol::this_state s, int n) {
    sol::state_view lua(s);
    std::cout << n << ". " << option << "\n";

    return sol::make_object(lua,
        [n](const sol::table&, sol::this_state s) -> sol::function {
            sol::state_view lua(s);
            return sol::make_object(lua,
                [n](const std::string& option, sol::this_state s) {
                    return options(option, s, n + 1);
                });
        });
}

sol::function options_root(const std::string& option, sol::this_state s)
{
    return options(option, s, 1);
}

void detail::setup_environment(sol::state& L)
{
    L.new_usertype<speaker>("speaker",
        sol::call_constructor,
        sol::factories([&L](const std::string& name) {
            auto spk = std::make_shared<speaker>(name);
            L[name] = spk;
            return spk;
        }),
        sol::meta_function::call,
        [](std::shared_ptr<speaker> speaker, const std::string& line) {
            std::cout << '[' << speaker->get_name() << "] " << line << '\n';
            return speaker;
        });

    L["section"] = [](const std::string& name) {
        std::cout << "===== NEW SECTION: " << name << " =====\n";
    };

    L["options"] = options_root;

    L["jump"] = [](const std::string&){};
}
