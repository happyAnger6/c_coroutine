#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "gtest/gtest.h"

#include "co.h"

static int g_counter = 0;
static co_wg_t g_wg;
static void co(void *args)
{
    g_counter++;
    co_wg_done(g_wg);
}

TEST(co_api, co_create_one) 
{
    coroutine_create(co, nullptr);
    g_wg = co_wg_create();
    co_wg_add(g_wg, 1);

    co_wg_wait(g_wg);
    EXPECT_EQ(g_counter, 1);
}