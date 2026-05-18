#include <iostream>
#include <atomic>  // std::atomic, fetch_add, fetch_sub, fetch_and, fetch_or, fetch_xor
#include <utility> // std::swap

template <typename T>
class MySharedPtr
{
private:
    struct ControlBlock
    {
        std::atomic<size_t> shared_count;
        std::atomic<size_t> weak_count;

        ControlBlock() : shared_count(1), weak_count(0) {}
    };

private:
    T *m_ptr;             // 指向真正被管理的对象
    ControlBlock *m_ctrl; // 指向控制块

private:
    void release()
    {
        if (m_ctrl == nullptr)
            return;

        // 当前 shared_ptr 不再管理该对象，强引用计数减 1
        size_t old_count = m_ctrl->shared_count.fetch_sub(1);

        // old_count 是减之前的值
        // 如果减之前是 1，说明减完以后 shared_count 变成 0
        if (old_count == 1)
        {
            // 释放被管理对象
            delete m_ptr;
            m_ptr = nullptr;

            // 如果没有 weak_ptr 指向控制块，控制块也可以释放
            if (m_ctrl->weak_count.load() == 0)
                delete m_ctrl;

            m_ctrl = nullptr;
        }
        else
        {
            // 还有其他 shared_ptr 管理该对象
            m_ptr = nullptr;
            m_ctrl = nullptr;
        }
    }

public:
    // ?[默认构造]
    MySharedPtr() : m_ptr(nullptr), m_ctrl(nullptr) {}

    // ?[裸指针构造]
    explicit MySharedPtr(T *ptr) : m_ptr(ptr)
    {
        if (m_ptr != nullptr)
            m_ctrl = new ControlBlock();
        else
            m_ctrl = nullptr;
    }

    // ?[析构函数]
    ~MySharedPtr()
    {
        release();
    }

    // ?[拷贝构造]
    MySharedPtr(const MySharedPtr &other) : m_ptr(other.m_ptr), m_ctrl(other.m_ctrl)
    {
        if (m_ctrl != nullptr)
            m_ctrl->shared_count.fetch_add(1);
    }

    // ?[赋值运算符=]
    MySharedPtr &operator=(const MySharedPtr &other)
    {
        if (this != &other)
        {
            // 先释放自己原来管理的资源
            release();

            // 再共享 other 的资源
            m_ptr = other.m_ptr;
            m_ctrl = other.m_ctrl;

            if (m_ctrl != nullptr)
                m_ctrl->shared_count.fetch_add(1);
        }

        return *this;
    }

    // ?[移动构造函数]
    // todo:与拷贝构造函数的不同点↓
    // 1.参数是右值引用：传入的参数是std::move()得到的“将亡值” or 匿名的临时对象“纯右值”
    // 2.不增加引用计数：移动构造是“转移所有权”，相当于直接接管资源，再将other置空
    MySharedPtr(MySharedPtr &&other) noexcept : m_ptr(other.m_ptr), m_ctrl(other.m_ctrl)
    {
        other.m_ptr = nullptr;
        other.m_ctrl = nullptr;
    }

    // ?[移动赋值运算符]
    MySharedPtr &operator=(MySharedPtr &&other) noexcept
    {
        if (this != &other)
        {
            // 先释放自己原来管理的资源
            release();

            // 接管 other 的资源
            m_ptr = other.m_ptr;
            m_ctrl = other.m_ctrl;

            // other 置空
            other.m_ptr = nullptr;
            other.m_ctrl = nullptr;
        }

        return *this;
    }

    // 8. 解引用运算符
    T &operator*() const
    {
        return *m_ptr;
    }

    // 9. 箭头运算符
    T *operator->() const
    {
        return m_ptr;
    }

    // 10. bool 转换
    explicit operator bool() const
    {
        return m_ptr != nullptr;
    }

    // 11. 获取裸指针
    T *get() const
    {
        return m_ptr;
    }

    // 12. 获取强引用计数
    size_t get_count() const
    {
        if (m_ctrl == nullptr)
        {
            return 0;
        }

        return m_ctrl->shared_count.load();
    }

    // 13. 判断是否唯一持有
    bool unique() const
    {
        return get_count() == 1;
    }

    // 14. reset：释放当前资源，变成空指针
    void reset()
    {
        release();
    }

    // 15. reset：释放旧资源，管理新资源
    void reset(T *ptr)
    {
        release();

        if (ptr != nullptr)
        {
            m_ptr = ptr;
            m_ctrl = new ControlBlock();
        }
        else
        {
            m_ptr = nullptr;
            m_ctrl = nullptr;
        }
    }

    // 16. swap
    void swap(MySharedPtr &other) noexcept
    {
        std::swap(m_ptr, other.m_ptr);
        std::swap(m_ctrl, other.m_ctrl);
    }
};