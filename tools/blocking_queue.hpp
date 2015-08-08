#include <condition_variable>
#include <list>
#include <boost/assert.hpp>

template<typename T>
class blocking_queue
{
public:
	blocking_queue() : _mutex(), _condvar(), _queue()
	{
	}

	void Put(const T& task)
	{
		{
			std::lock_guard<std::mutex> lock(_mutex);
			_queue.push_back(task);
		}
		_condvar.notify_all();
	}

	T Take()
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_condvar.wait(lock, [this]{return !_queue.empty(); });
		BOOST_ASSERT_MSG(!_queue.empty(), "Blocking queue is empty, but get an element.");
		T front(_queue.front());
		_queue.pop_front();

		return front;
	}

	size_t Size() const
	{
		std::lock_guard<std::mutex> lock(_mutex);
		return _queue.size();
	}

private:
	blocking_queue(const blocking_queue& rhs);
	blocking_queue& operator = (const blocking_queue& rhs);

private:
	mutable std::mutex _mutex;
	std::condition_variable _condvar;
	std::list<T> _queue;
};