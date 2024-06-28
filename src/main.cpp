#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <shellapi.h>



enum console_colors
{
	black_foreground = 0,
	maroon_foreground = FOREGROUND_RED,
	green_foreground = FOREGROUND_GREEN,
	navy_foreground = FOREGROUND_BLUE,
	teal_foreground = FOREGROUND_GREEN | FOREGROUND_BLUE,
	olive_foreground = FOREGROUND_RED | FOREGROUND_GREEN,
	purple_foreground = FOREGROUND_RED | FOREGROUND_BLUE,
	gray_foreground = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	silver_foreground = FOREGROUND_INTENSITY,
	red_foreground = FOREGROUND_INTENSITY | FOREGROUND_RED,
	lime_foreground = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	blue_foreground = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	aqua_foreground = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	yellow_foreground = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	fuchsia_foreground = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	white_foreground = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
};



int main()
{
    SetConsoleTitleA("Microsoft Store Apps EXE Downloader");

    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(output, console_colors::teal_foreground);

    std::cout << R"($$\      $$\ $$\                                                    $$$$$$\    $$\     
$$$\    $$$ |\__|                                                  $$  __$$\   $$ |    
$$$$\  $$$$ |$$\  $$$$$$$\  $$$$$$\   $$$$$$\   $$$$$$$\  $$$$$$\  $$ /  \__|$$$$$$\   
$$\$$\$$ $$ |$$ |$$  _____|$$  __$$\ $$  __$$\ $$  _____|$$  __$$\ $$$$\     \_$$  _|  
$$ \$$$  $$ |$$ |$$ /      $$ |  \__|$$ /  $$ |\$$$$$$\  $$ /  $$ |$$  _|      $$ |    
$$ |\$  /$$ |$$ |$$ |      $$ |      $$ |  $$ | \____$$\ $$ |  $$ |$$ |        $$ |$$\ 
$$ | \_/ $$ |$$ |\$$$$$$$\ $$ |      \$$$$$$  |$$$$$$$  |\$$$$$$  |$$ |        \$$$$  |
\__|     \__|\__| \_______|\__|       \______/ \_______/  \______/ \__|         \____/
Store Apps EXE Downloader
                                                          
)";

    while (true)
    {
        SetConsoleTextAttribute(output, console_colors::gray_foreground);

        std::cout << "Url: ";

        std::string input;
        std::getline(std::cin, input);

        bool is_url_valid = true;

        if (input.empty())
        {
            is_url_valid = false;
        }

        if (!input.contains("apps.microsoft.com/detail/"))
        {
            is_url_valid = false;
        }

        size_t index = input.find_last_of('/');

        if (index == std::string::npos)
        {
            is_url_valid = false;
        }

        if (is_url_valid)
        {
            size_t index2 = input.find_first_of('?');

            if (index2 == std::string::npos)
            {
                input = input.substr(index + 1, input.size() - 1);
            }
            else
            {
                input = input.substr(index + 1, index2 - index - 1);
            }

            if (!input.empty())
            {
                ShellExecuteA(NULL, "open", ("https://get.microsoft.com/installer/download/" + input).c_str(), NULL, NULL, SW_HIDE);
            }
            else
            {
                SetConsoleTextAttribute(output, console_colors::red_foreground);

                std::cerr << "Failed: Empty app id" << std::endl;
            }
        }
        else
        {
            SetConsoleTextAttribute(output, console_colors::red_foreground);

            std::cerr << "Failed: Invalid url" << std::endl;
        }
    }
}