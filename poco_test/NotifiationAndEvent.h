#include "Poco/NotificationCenter.h"
#include "Poco/Notification.h"
#include "Poco/Observer.h"
#include "Poco/NObserver.h"
#include "Poco/AutoPtr.h"
#include <iostream>
using Poco::NotificationCenter;
using Poco::Notification;
using Poco::Observer;
using Poco::NObserver;
using Poco::AutoPtr;

class BaseNotification: public Notification
{
};
class SubNotification: public BaseNotification
{
};

class Target
{
public:
	void handleBase(BaseNotification* pNf)
	{
		std::cout << "handleBase: " << pNf->name() << std::endl;
		pNf->release(); // we got ownership, so we must release
	}
	void handleSub(const AutoPtr<SubNotification>& pNf)
	{
		std::cout << "handleSub: " << pNf->name() << std::endl;
	}
};

void testNotificationPolymorphism()
{
	NotificationCenter nc;
	Target target;

	nc.addObserver(
		Observer<Target, BaseNotification>(target, &Target::handleBase)
		);
	nc.addObserver(
		NObserver<Target, SubNotification>(target, &Target::handleSub)
		);

	nc.postNotification(new BaseNotification);
	nc.postNotification(new SubNotification);

	nc.removeObserver(
		Observer<Target, BaseNotification>(target, &Target::handleBase)
		);
	nc.removeObserver(
		NObserver<Target, SubNotification>(target, &Target::handleSub)
		);
}

#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include "Poco/AutoPtr.h"
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Runnable;
using Poco::AutoPtr;

class WorkNotification: public Notification
{
public:
	WorkNotification(int data): _data(data) {}
	int data() const
	{
		return _data;
	}
private:
	int _data;
};

class Worker: public Runnable
{
public:
	Worker(NotificationQueue& queue): _queue(queue) {}
	void run()
	{
		AutoPtr<Notification> pNf(_queue.waitDequeueNotification());
		while (pNf)
		{
			WorkNotification* pWorkNf =
				dynamic_cast<WorkNotification*>(pNf.get());
			if (pWorkNf)
			{
				std::cout << pWorkNf->data() << ", ";
			}
			pNf = _queue.waitDequeueNotification();
		}
	}
private:
	NotificationQueue& _queue;
};

void testNotificationQueue()
{
	NotificationQueue queue;
	Worker worker1(queue); // create worker threads
	Worker worker2(queue);

	ThreadPool::defaultPool().start(worker1); // start workers
	ThreadPool::defaultPool().start(worker2);

	// create some work
	for (int i = 0; i < 100; ++i)
	{
		queue.enqueueNotification(new WorkNotification(i));
		Poco::Thread::sleep(0);	// sleep이 0이 아니면, Worker의 run에서 i가 0, 1이 함께 프린트된다.
	}
	while (!queue.empty()) // wait until all work is done
		Poco::Thread::sleep(1000);

	queue.wakeUpAll(); // tell workers they're done
	ThreadPool::defaultPool().joinAll();
}

#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
#include <iostream>
using Poco::BasicEvent;
using Poco::Delegate;

class EventSource
{
public:
	BasicEvent<int> theEvent;
	void fireEvent(int n)
	{
		theEvent(this, n);
		// theEvent.notify(this, n); // alternative syntax
	}
};

class EventTarget
{
public:
	void onEvent(const void* pSender, int& arg)
	{
		std::cout << std::endl << "onEvent: " << arg << std::endl;
	}
};

void testEvent()
{
	EventSource source;
	EventTarget target;

	source.theEvent += Poco::delegate(&target, &EventTarget::onEvent);
	source.fireEvent(42);
	source.theEvent -= Poco::delegate(&target, &EventTarget::onEvent);
}