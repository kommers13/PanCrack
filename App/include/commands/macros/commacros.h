#ifndef COMMACROS_H
#define COMMACROS_H


// данный макрос проверяет правильность введенных флагов
// может остановить выполнение функции, если был найден флаг, которого не существует
// на вход подается имя команды и вектор опций, который ввел пользователь
#define VALIDATE_COMMAND_FLAGS(command, opts) \
do { \
        output = "<br>You may input <b>" + command + " --help</b> for more information."; \
        auto com_inf = list_commands::get(command); \
        description = get<1>(com_inf); \
        unordered_map<string, string> got_opts = get<2>(com_inf); \
        for (string opt: opts) { \
            if (got_opts[opt] == "") { \
                output = "Flag <b>" + opt + "</b> wasn`t found." + output; \
                return output; \
        } \
    } \
}\
while(0)


#endif // COMMACROS_H
