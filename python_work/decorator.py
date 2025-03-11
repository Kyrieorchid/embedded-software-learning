'''装饰器：可以增强函数的功能，
在其执行前后加一层“装饰”，
在不改变函数本身的情况下实现额外功能'''
import time, functools

def metric(fn):
    @functools.wraps(fn)
    def wrapper(*args, **kv):
        print("%s executed in %s ms" % (fn.__name__, 3.10))
        return fn(*args, **kv)
    return wrapper

# 测试
@metric
def fast(x, y):
    time.sleep(0.0012)
    return x + y;

@metric
def slow(x, y, z):
    time.sleep(0.1234)
    return x * y * z;

f = fast(11, 22)
s = slow(11, 22, 33)
if f != 33 or s != 7986:
    print('测试失败!')
else:
    print("测试成功!")

print("###################################################")

def decorator(fn):
    @functools.wraps(fn)
    def wrapper(*args, **kv):
        print("begin call %s:" % fn.__name__)
        fn(*args, **kv)
        print("end call %s:" % fn.__name__)
    return wrapper

#测试
@decorator
def add(x, y):
    print("%s + %s = %s" % (x, y, (x + y)))

add(1, 3)
print("###################################################")

def log(text = None):
    def decorator(fn):
        @functools.wraps(fn)
        def wrapper(*args, **kv):
            if text is None:
                print("call %s" % fn.__name__)
            else:
                print("%s %s, decorate test" % (text, fn.__name__))
            return fn(*args, **kv)
        return wrapper
    return decorator

def log(fn):
    @functools.wraps(fn)
    def wrapper(*args, **kv):
            print("call %s" % fn.__name__)
            return fn(*args, **kv)
    return wrapper

@log
def f1():
    print("f1 without log text")

@log("execute")
def f2():
    print("f2 with log text")

f1()
f2()
