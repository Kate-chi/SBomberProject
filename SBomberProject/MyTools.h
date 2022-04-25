#pragma once

#include <stdint.h>
#include <string>

namespace MyTools {

    // Палитра цветов от 0 до 15
    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

	//=============================================================================================

	void ClrScr();

	void __fastcall GotoXY(double x, double y);

	uint16_t GetMaxX();

	uint16_t GetMaxY();

    void SetColor(ConsoleColor color);

	//=============================================================================================

	void __fastcall OpenLogFile(const std::string& FN);

	void CloseLogFile();

	void __fastcall WriteToLog(const std::string& str);

	void __fastcall WriteToLog(const std::string& str, int n);

	void __fastcall WriteToLog(const std::string& str, double d);

	//=============================================================================================
    
    class ILogger
    {
    public:
        virtual ~ILogger() = default;
        virtual void __fastcall OpenLogFile(const std::string& FN) = 0;
        virtual void CloseLogFile() = 0;
        virtual void __fastcall WriteToLog(const std::string& str) = 0;
        virtual void __fastcall WriteToLog(const std::string& str, int n) = 0;
        virtual void __fastcall WriteToLog(const std::string& str, double d) = 0;
    };

    class FileLoggerSingletone : public ILogger
    {
    public:
        static FileLoggerSingletone& getInstance()
        {
            static FileLoggerSingletone theInstanse;
            return theInstanse;
        }

        void __fastcall OpenLogFile(const std::string& FN);
        void CloseLogFile();
        void __fastcall WriteToLog(const std::string& str);
        void __fastcall WriteToLog(const std::string& str, int n);
        void __fastcall WriteToLog(const std::string& str, double d);

    private:
        FileLoggerSingletone() {}
        FileLoggerSingletone(const FileLoggerSingletone& root) = delete;
        FileLoggerSingletone& operator=(const FileLoggerSingletone&) = delete;
        FileLoggerSingletone(FileLoggerSingletone&&) = delete;
        FileLoggerSingletone& operator=(FileLoggerSingletone&&) = delete;

        std::ofstream logOut;

    };

    class ProxyLogger : public ILogger
    {
    public:
        ProxyLogger(ILogger& logger) : logger{logger} {}
        ~ProxyLogger() override;

        void __fastcall OpenLogFile(const std::string& FN) override;
        void CloseLogFile() override;
        void __fastcall WriteToLog(const std::string& str) override;
        void __fastcall WriteToLog(const std::string& str, int n) override;
        void __fastcall WriteToLog(const std::string& str, double d) override;

    private:
        ILogger& logger;
        int32_t counter;
    };

};