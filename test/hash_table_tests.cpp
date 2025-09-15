/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_tests.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:37:17 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/15 15:17:16 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <string>
#include <vector>
#include <gtest/gtest.h>

extern "C" {
#include "ds/hash_table.h"
}

class HashTableTest : public ::testing::Test {
protected:
	t_hash_table ht{};

	void SetUp() override
	{
		ASSERT_EQ(hash_table_init(&ht), 0) << "hash_table_init must return 0";
		ASSERT_NE(ht.table, nullptr);
		ASSERT_GT(ht.table_size, 0u);
	}

	void TearDown() override
	{
		hash_table_destroy(&ht);
	}
};

TEST_F(HashTableTest, InsertAndSearchSingle)
{
	const char *cmd = "ls";
	const char *path = "/bin/ls";

	ASSERT_EQ(hash_table_insert(&ht, cmd, path), 0);
	char *found = hash_table_search(&ht, cmd);
	ASSERT_NE(found, nullptr);
	EXPECT_STREQ(found, path);
}

TEST_F(HashTableTest, SearchUnknownReturnsNull)
{
	EXPECT_EQ(hash_table_search(&ht, "does-not-exist"), nullptr);
}

TEST_F(HashTableTest, InsertReplaceSameKey)
{
	ASSERT_EQ(hash_table_insert(&ht, "cat", "/bin/cat"), 0);
	char *p1 = hash_table_search(&ht, "cat");
	ASSERT_NE(p1, nullptr);
	EXPECT_STREQ(p1, "/bin/cat");
	ASSERT_EQ(hash_table_insert(&ht, "cat", "/usr/bin/cat"), 0);
	char *p2 = hash_table_search(&ht, "cat");
	ASSERT_NE(p2, nullptr);
	EXPECT_STREQ(p2, "/usr/bin/cat");
}

TEST_F(HashTableTest, DeleteExisting)
{
	ASSERT_EQ(hash_table_insert(&ht, "echo", "/bin/echo"), 0);
	ASSERT_NE(hash_table_search(&ht, "echo"), nullptr);
	ASSERT_EQ(hash_table_delete(&ht, "echo"), 0);
	EXPECT_EQ(hash_table_search(&ht, "echo"), nullptr);
}

TEST_F(HashTableTest, DeleteUnknownIsGraceful)
{
	const int32_t rc = hash_table_delete(&ht, "missing");
	ASSERT_EQ(hash_table_insert(&ht, "x", "/bin/x"), 0);
	ASSERT_NE(hash_table_search(&ht, "x"), nullptr);
	(void) rc;
}

TEST_F(HashTableTest, ResetClearsAll)
{
	ASSERT_EQ(hash_table_insert(&ht, "sh", "/bin/sh"), 0);
	ASSERT_EQ(hash_table_insert(&ht, "bash", "/bin/bash"), 0);
	ASSERT_NE(hash_table_search(&ht, "sh"), nullptr);
	ASSERT_NE(hash_table_search(&ht, "bash"), nullptr);
	hash_table_reset(&ht);
	EXPECT_EQ(hash_table_search(&ht, "sh"), nullptr);
	EXPECT_EQ(hash_table_search(&ht, "bash"), nullptr);
	ASSERT_EQ(hash_table_insert(&ht, "zsh", "/bin/zsh"), 0);
	ASSERT_NE(hash_table_search(&ht, "zsh"), nullptr);
}

TEST_F(HashTableTest, ManyInsertionsAndLookups)
{
	constexpr size_t N = 1000;
	std::vector<std::string> keys;
	std::vector<std::string> values;
	keys.reserve(N);
	values.reserve(N);

	for (size_t i = 0; i < N; ++i)
	{
		std::ostringstream k, v;
		k << "cmd_" << i;
		v << "/bin/cmd_" << i;
		keys.push_back(k.str());
		values.push_back(v.str());
		ASSERT_EQ(hash_table_insert(&ht, keys.back().c_str(), values.back().c_str()),
				0) << "Insertion failed at i=" << i;
	}
	for (size_t i = 0; i < N; ++i)
	{
		char *found = hash_table_search(&ht, keys[i].c_str());
		ASSERT_NE(found, nullptr) << "Not found for i=" << i;
		EXPECT_STREQ(found, values[i].c_str()) << "Unexpected path for i=" << i;
	}
}

TEST_F(HashTableTest, DeleteThenInsertNewKeyStillSearchable)
{
	ASSERT_EQ(hash_table_insert(&ht, "alpha", "/bin/alpha"), 0);
	ASSERT_EQ(hash_table_insert(&ht, "beta", "/bin/beta"), 0);
	ASSERT_EQ(hash_table_delete(&ht, "alpha"), 0);
	ASSERT_EQ(hash_table_insert(&ht, "gamma", "/bin/gamma"), 0);
	ASSERT_NE(hash_table_search(&ht, "gamma"), nullptr);
	EXPECT_EQ(hash_table_search(&ht, "alpha"), nullptr);
}

TEST_F(HashTableTest, InsertEmptyStringsAndEdgeCases)
{
	if (const int32_t rc_key_empty = hash_table_insert(&ht, "", "/bin/empty"); rc_key_empty == 0)
	{
		char *p = hash_table_search(&ht, "");
		ASSERT_NE(p, nullptr);
		EXPECT_STREQ(p, "/bin/empty");
	}
	ASSERT_EQ(hash_table_insert(&ht, "nop", ""), 0);
	char *pv = hash_table_search(&ht, "nop");
	ASSERT_NE(pv, nullptr);
	EXPECT_STREQ(pv, "");
}

TEST_F(HashTableTest, InsertNullArgumentsAreRejected)
{
	(void) hash_table_insert(&ht, nullptr, "/bin/null");
	(void) hash_table_insert(&ht, "null", nullptr);
	ASSERT_EQ(hash_table_insert(&ht, "ok", "/bin/ok"), 0);
	ASSERT_NE(hash_table_search(&ht, "ok"), nullptr);
}
