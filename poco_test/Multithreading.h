#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include <iostream>

class HelloRunnable: public Poco::Runnable
{
	virtual void run()
	{
		std::cout << "HelloRunnable : Hello, world!" << std::endl;
	}
};

void testRunnable()
{
	HelloRunnable runnable;
	Poco::Thread thread;

	thread.start(runnable);
	thread.join();
}

#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"
#include <iostream>

class Greeter
{
public:
	void greet()
	{
		std::cout << "Greeter : Hello, world!" << std::endl;
	}
};

void testRunnableAdapter()
{
	Greeter greeter;
	Poco::RunnableAdapter<Greeter> runnable(greeter, &Greeter::greet);
	Poco::Thread thread;

	thread.start(runnable);
	thread.join();
}

#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include <iostream>

class TPHelloRunnable: public Poco::Runnable
{
	virtual void run()
	{
		std::cout << "TPHelloRunnable : Hello, world!" << std::endl;
	}
};

void testThreadPool()
{
	TPHelloRunnable runnable;

	Poco::ThreadPool::defaultPool().start(runnable);
	Poco::ThreadPool::defaultPool().joinAll();
}

#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/ThreadLocal.h"
#include <iostream>

class Counter: public Poco::Runnable
{
	void run()
	{
		static Poco::ThreadLocal<int> tls;
		static int thread_int = 0;

		for (*tls = 0; *tls < 10; ++(*tls))
		{
			std::cout << _threadid << ": (ThreadLocal int, Thread int) = " << *tls << ", " << thread_int++ << std::endl;
		}
	}
};

void testThreadLocalStorage()
{
	Counter counter;
	Poco::Thread t1;
	Poco::Thread t2;

	t1.start(counter);
	t2.start(counter);
	t1.join();
	t2.join();
}

#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/ErrorHandler.h"
#include <iostream>

class Offender: public Poco::Runnable
{
	void run()
	{
		throw Poco::ApplicationException("got you");
	}
};

class MyErrorHandler: public Poco::ErrorHandler
{
public:
	void exception(const Poco::Exception& exc)
	{
		std::cerr << "Poco::Execption> " << exc.displayText() << std::endl;
	}
	void exception(const std::exception& exc)
	{
		std::cerr << "std::execption> " << exc.what() << std::endl;
	}
	void exception()
	{
		std::cerr << "unknown exception" << std::endl;
	}
};

void testThreadErrorHandler()
{
	MyErrorHandler eh;
	Poco::ErrorHandler* pOldEH = Poco::ErrorHandler::set(&eh);

	Offender offender;
	Poco::Thread thread;

	thread.start(offender);
	thread.join();

	//Poco::ErrorHandler::set(pOldEH);	// 없어도 동작하는데... 왜 넣었을까??
}

#include "Poco/Timer.h"
#include "Poco/Thread.h"
using Poco::Timer;
using Poco::TimerCallback;

class TimerExample
{
public:
	void onTimer(Poco::Timer& timer)
	{
		Poco::LocalDateTime now;
		std::string s = DateTimeFormatter::format(now, "%Y-%m-%d %H:%M:%S.%F");
		std::cout << "onTimer called at " << s << std::endl;
	}
};

void testTimer()
{
	TimerExample te;
	Timer timer(250, 500); // fire after 250ms, repeat every 500ms
	timer.start(TimerCallback<TimerExample>(te, &TimerExample::onTimer));

	Poco::Thread::sleep(5000);
	timer.stop();
}

#include "Poco/Task.h"
#include "Poco/TaskManager.h"
#include "Poco/TaskNotification.h"
#include "Poco/Observer.h"
using Poco::Observer;

class SampleTask: public Poco::Task
{
public:
	SampleTask(const std::string& name): Task(name)
	{}
	void runTask()
	{
		for (int i = 0; i < 10; ++i)
		{
			setProgress(float(i)/100); // report progress
			if (sleep(1000))
				break;
		}
	}
};

class ProgressHandler
{
public:
	void onProgress(Poco::TaskProgressNotification* pNf)
	{
		std::cout << pNf->task()->name() << " progress: " << pNf->progress() << std::endl;
		pNf->release();
	}
	void onFinished(Poco::TaskFinishedNotification* pNf)
	{
		std::cout << pNf->task()->name() << " finished." << std::endl;
		pNf->release();
	}
};

void testTaskNotification()
{
	Poco::TaskManager tm;
	ProgressHandler pm;

	tm.addObserver(
		Observer<ProgressHandler, Poco::TaskProgressNotification>
		(pm, &ProgressHandler::onProgress)
		);
	tm.addObserver(
		Observer<ProgressHandler, Poco::TaskFinishedNotification>
		(pm, &ProgressHandler::onFinished)
		);
	tm.start(new SampleTask("Task 1")); // tm takes ownership
	tm.start(new SampleTask("Task 2"));
	tm.joinAll();
}

#include "Poco/Activity.h"
#include "Poco/Thread.h"
#include <iostream>
using Poco::Thread;

class ActivityExample
{
public:
	ActivityExample(): _activity(this, &ActivityExample::runActivity)
	{}
	void start()
	{
		_activity.start();
	}
	void stop()
	{
		_activity.stop(); // request stop
		_activity.wait(); // wait until activity actually stops
	}
protected:
	void runActivity()
	{
		while (!_activity.isStopped())
		{
			std::cout << "Activity running." << std::endl;
			Thread::sleep(200);
		}
	}
private:
	Poco::Activity<ActivityExample> _activity;
};

void testActivity()
{
	ActivityExample example;
	example.start();
	Thread::sleep(2000);
	example.stop();
}

#include "Poco/ActiveMethod.h"
#include "Poco/ActiveResult.h"
#include <utility>
using Poco::ActiveMethod;
using Poco::ActiveResult;

class ActiveAdder
{
public:
	ActiveAdder():
	  add(this, &ActiveAdder::addImpl)
	  {}
	  ActiveMethod<int, std::pair<int, int>, ActiveAdder> add;
private:
	int addImpl(const std::pair<int, int>& args)
	{
		return args.first + args.second;
	}
};

void testActiveMethod()
{
	ActiveAdder adder;

	ActiveResult<int> sum = adder.add(std::make_pair(1, 2));
	sum.wait();
	std::cout << sum.data() << std::endl;
}

#include "Poco/ActiveMethod.h"
#include "Poco/ActiveResult.h"
#include "Poco/ActiveDispatcher.h"
#include <utility>
using Poco::ActiveMethod;
using Poco::ActiveResult;

class ActiveAdder2: public Poco::ActiveDispatcher
{
public:
	ActiveAdder2(): add(this, &ActiveAdder2::addImpl)
	{}
	ActiveMethod<int, std::pair<int, int>, ActiveAdder2,
		Poco::ActiveStarter<Poco::ActiveDispatcher> > add;
private:
	int addImpl(const std::pair<int, int>& args)
	{
		return args.first + args.second;
	}
};

void testActiveDispatcher()
{
	ActiveAdder2 adder;
	ActiveResult<int> sum = adder.add(std::make_pair(1, 2));
	sum.wait();
	std::cout << sum.data() << std::endl;
}