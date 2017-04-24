#ifndef MUDUO_BASE_NONCOPYABLE_H
#define MUDUO_BASE_NONCOPYABLE_H
namespace wuduo
{
struct Noncopyable
{
	Noncopyable() = default;
	Noncopyable(const Noncopyable&) = delete;
	Noncopyable &operator=(const Noncopyable&) = delete;
	~Noncopyable() = default;
};
}
#endif
