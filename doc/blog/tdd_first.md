# libco开发教程(一) ---- 第一个例子

## libco背景

关于`libco`的背景,可以看我之前的文章,[在c中实现协程](https://blog.csdn.net/happyAnger6/article/details/118466471?spm=1001.2014.3001.5501)

前一段时间一直在忙换工作的事情,因此`c语言协程库`的开发有一些搁浅.  
最近换工作的事情告一段落了,代码实现也就提上了日程.  
感兴趣的小伙伴可以跟着我的教程一步一步实践,最终实现一个功能完善能够在生产中使用的`c协程库`.  

## TDD

项目以`TDD`测试驱动开发的方式进行编码,我们先来编写一个最简单的测试用例

### test case

```cpp
#include "gtest/gtest.h"

#include "co.h"
#include "sync/co_wg.h"

static int g_counter = 0;
static co_wg_t g_wg;
static void co(void *args)
{
    g_counter++; // 协程将全局变量加1.
    co_wg_done(g_wg); // 将waitGroup计数减1,通知主线程结束.
}

TEST(co_api, co_create_one) 
{
    coroutine_create(co, nullptr); // 创建一个协程,入口函数为co
    g_wg = co_wg_create();  // 创建一个waitGroup,类似于golang中的waitGroup,用于主线程和协程之间同步.
    co_wg_add(g_wg, 1); // 将waitGroup计数加1.

    co_wg_wait(g_wg); // 等待协程结束
    EXPECT_EQ(g_counter, 1); // 检查协程是否正常结束并设置了全局变量g_counter.
}
```

通过测试用例可以看到,我们希望协程库的最终使用方式如上所示.  
其中`co_wg_t`参考了golang中的`waitGroup`,用于同步功能.  
可以看出,api还是比较简洁清晰的,下面详细介绍一下api的功能.

### api

#### extern co_t co_create(co_func fn, void *args)

##### 功能: 创建一个协程

+ `co_func fn`: 协程入口函数
+ `void *args`: 协程参数

###### co_wg_t主要是参考了golang中的`waitGroup`,用于同步功能.

#### extern co_wg_t co_wg_create();
##### 功能: 创建一个co_wg_t

#### extern void co_wg_add(co_wg_t wg, int val);
##### 功能: 将wg的值增加val

+ `co_wg_t wg`: `co_wg_create`创建的wg
+ `int val`: wg要增加的计数

#### extern void co_wg_done(co_wg_t wg);
##### 功能: 将wg的值减1

+ `co_wg_t wg`: `co_wg_create`创建的wg

#### extern void co_wg_wait(co_wg_t wg);
##### 功能: 等待wg计数变为0

+ `co_wg_t wg`: `co_wg_create`创建的wg


测试用例完了,下一步就是编写代码让我们的测试用例能够成功执行了.