#pragma once

class Framebuffer
{
public:
    Framebuffer();
    ~Framebuffer() = default;

    Framebuffer(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    Framebuffer(Framebuffer&&) = delete;
    Framebuffer& operator=(Framebuffer&&) = delete;

    void Print(const char* string);

private:
    char* _address;
    int _index;

    void GoToNextLine();
};
