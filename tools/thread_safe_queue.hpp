#pragma once
#ifndef CTI_THREAD_SAFE_DEQUE_HPP_INCLUDED
#define CTI_THREAD_SAFE_DEQUE_HPP_INCLUDED
#include <queue>
#include <stdexcept>
#include <boost/thread.hpp>

/**
 * 封装一个线程安全的deque队列， 用于队列操作
 *
 * @author LYL QQ-331461049
 * @date 2015/07/20 9:32
 */
template<typename T>
class thread_safe_queue
{
private:
	boost::mutex			_mutex;
	std::queue<T>    _container;

public:
	//thread_safe_deque(int container_init_capacity)
	//{
	//	_container.reserve(container_init_capacity);
	//}

	void put(const T& task)
	{
		_mutex.lock();
		_container.push(task);
		_mutex.unlock();
	}

	T take()
	{
		_mutex.lock();
		if (_container.size() == 0) {
			_mutex.unlock();
			throw std::out_of_range("container is null");    //返回异常， 主要因为容器中的元素可能为指针， 也可能为基本类型 如 int， 则在为空的情况下返回 NULL 或 0都不合适			
		}
		T front = _container.front();
		_container.pop();
		_mutex.unlock();
		return front;
	}

	size_t size()
	{
		_mutex.lock();
		size_t c_size = _container.size();
		_mutex.unlock();
		return c_size;
	}
};

#endif	//CTI_THREAD_SAFE_DEQUE_HPP_INCLUDED