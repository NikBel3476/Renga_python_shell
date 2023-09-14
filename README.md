# Renga_python_shell

---

**По итогу, я признал это бесперспективным и сложным в разработке. Так что развития приложения не будет, пока Renga не предоставит не-COM API.**

---

Repa (РЕнга ПАйтон) -- плагин в Renga для исполнения скриптов на Python, с **(в планах)** рядом портированных на Python вспомогательных конструкций с языка C++, включая альтернативные варианты доступа к объектной модели (не только через официальный SDK), написан на фрейморке QT 6 (6.2.3).

![](/logo/repa_logo.png)

# Об установке и версии обновлений

См. файл [release_notes](/release_notes.md)

Сборка проекта (CMake)

1. cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=<path to qt6> -DRENGA_SDK_PATH=<path to renga SDK> -B <build directory>
2. cmake --build <build directory> --target renga_py_shell
