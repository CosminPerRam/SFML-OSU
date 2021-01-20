
#pragma once

struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable& operator = (const NonCopyable&) = delete;
    NonCopyable(const NonCopyable&) = delete;
};

struct NonMovable
{
    NonMovable() = default;
    NonMovable& operator = (NonMovable&&) = delete;
    NonMovable(NonCopyable&&) = delete;
};