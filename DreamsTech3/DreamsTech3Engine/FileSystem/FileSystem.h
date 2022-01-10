#pragma once

class FileSystem
{
public:
    static FileSystem& getInstance()
    {
        static FileSystem    instance;

        return instance;
    }





private:
    FileSystem() {}


public:
    FileSystem(FileSystem const&) = delete;
    void operator=(FileSystem const&) = delete;


};