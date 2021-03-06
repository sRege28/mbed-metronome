/*
 * Copyright (c) 2015 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "CppUTest/TestHarness.h"
#include "test_m2mtlvserializer.h"
#include "m2mobject_stub.h"
#include "m2mobjectinstance_stub.h"
#include "m2mresource_stub.h"
#include "m2mresourceinstance_stub.h"
#include "m2mbase_stub.h"

/* Counters and malloc wrap function for out of memory testing
   using GCC linker option. */
extern "C" {
    static unsigned int memory_fail_counter=0;
    static unsigned int memory_will_fail_counter=0;

    void *__real_malloc(size_t bytes);

    void *__wrap_malloc(size_t size) {

        if (memory_fail_counter && !memory_will_fail_counter) {
            memory_fail_counter--;
            return 0;
        } else {
            if (memory_will_fail_counter) {
                memory_will_fail_counter--;
            }
            return __real_malloc(size);
        }
    }
}

Test_M2MTLVSerializer::Test_M2MTLVSerializer()
{
    serializer = new M2MTLVSerializer();
}

Test_M2MTLVSerializer::~Test_M2MTLVSerializer()
{
    delete serializer;
}

void Test_M2MTLVSerializer::test_serialize_object_out_of_memory()
{
    uint32_t size = 0;
    uint8_t *data = 0;

    M2MObject *object = new M2MObject("1", "1");
    M2MObjectInstance* instance = new M2MObjectInstance(*object,"1", "type", "1");

    m2mobject_stub::instance_list.push_back(instance);



    M2MResource* resource = new M2MResource(*instance,
                                            "1",
                                            "type",
                                            M2MResourceInstance::INTEGER,
                                            false,
                                            "1");


    m2mobjectinstance_stub::resource_list.push_back(resource);

    m2mbase_stub::name_id_value = 0;
    memory_fail_counter=1; //apply for 1 time failing malloc
    memory_will_fail_counter=3; //after 3 successful ones
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data == NULL);

    memory_fail_counter=1; //apply for 1 time failing malloc
    memory_will_fail_counter=4; //after 4 successful ones
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data == NULL);

    M2MResourceInstance* res_instance =  new M2MResourceInstance(*m2mobjectinstance_stub::resource,
                                                                 "1",
                                                                 "type",
                                                                 M2MResourceInstance::STRING,
                                                                 0,
                                                                 "1",
                                                                 false);

    M2MResourceInstance* res_instance_1 =  new M2MResourceInstance(*m2mobjectinstance_stub::resource,
                                                                   "2",
                                                                   "type",
                                                                   M2MResourceInstance::STRING,
                                                                   0,
                                                                   "2",
                                                                   false);

    m2mresource_stub::bool_value = true;
    m2mresource_stub::list.push_back(res_instance);
    m2mresource_stub::list.push_back(res_instance_1);
    memory_fail_counter=1; //apply for 1 time failing malloc
    memory_will_fail_counter=4; //after 4 successful ones
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data == NULL);

    memory_fail_counter=1; //apply for 1 time failing malloc
    memory_will_fail_counter=5; //after 5 successful ones
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data == NULL);

    memory_fail_counter=1; //apply for 1 time failing malloc
    memory_will_fail_counter=6; //after 6 successful ones
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data == NULL);

    memory_fail_counter=1; //apply for 1 time failing malloc
    memory_will_fail_counter=7; //after 7 successful ones
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data == NULL);

    delete res_instance_1;
    delete res_instance;
    delete resource;
    delete instance;
    delete object;

    m2mresourceinstance_stub::clear();
    m2mresource_stub::clear();
    m2mobjectinstance_stub::clear();
    m2mobject_stub::clear();
}

void Test_M2MTLVSerializer::test_serialize_object()
{
    uint32_t size = 0;
    uint8_t *data = 0;

    M2MObject *object = new M2MObject("1", "1");
    M2MObjectInstance* instance = new M2MObjectInstance(*object,"1", "type", "1");

    m2mobject_stub::instance_list.push_back(instance);



    M2MResource* resource = new M2MResource(*instance,
                                            "1",
                                            "type",
                                            M2MResourceInstance::INTEGER,
                                            false,
                                            "1");


    m2mobjectinstance_stub::resource_list.push_back(resource);

    m2mbase_stub::name_id_value = 0;
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data != NULL);

    if(data) {
        free(data);
        data = 0;
    }

    M2MResourceInstance* res_instance =  new M2MResourceInstance(*m2mobjectinstance_stub::resource,
                                                                 "1",
                                                                 "type",
                                                                 M2MResourceInstance::STRING,
                                                                 0,
                                                                 "1",
                                                                 false);

    M2MResourceInstance* res_instance_1 =  new M2MResourceInstance(*m2mobjectinstance_stub::resource,
                                                                   "2",
                                                                   "type",
                                                                   M2MResourceInstance::STRING,
                                                                   0,
                                                                   "2",
                                                                   false);


    m2mresource_stub::bool_value = true;
    m2mresource_stub::list.push_back(res_instance);
    m2mresource_stub::list.push_back(res_instance_1);
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data != NULL);

    if(data) {
        free(data);
        data = 0;
    }

    m2mbase_stub::name_id_value = 256;

    m2mresourceinstance_stub::int_value = 6;
    m2mresourceinstance_stub::value = (uint8_t*) malloc(m2mresourceinstance_stub::int_value);
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data != NULL);

    if(data) {
        free(data);
        data = 0;
    }
    free(m2mresourceinstance_stub::value);
    m2mresourceinstance_stub::value = NULL;

    m2mresourceinstance_stub::int_value = 256;
    m2mresourceinstance_stub::value = (uint8_t*) malloc(m2mresourceinstance_stub::int_value);
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data != NULL);

    if(data) {
        free(data);
        data = 0;
    }
    free(m2mresourceinstance_stub::value);
    m2mresourceinstance_stub::value = NULL;

    m2mresourceinstance_stub::int_value = 65536;
    m2mresourceinstance_stub::value = (uint8_t*) malloc(m2mresourceinstance_stub::int_value);
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data != NULL);

    if(data) {
        free(data);
        data = 0;
    }

    m2mbase_stub::name_id_value = -1;
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data == NULL);

    delete res_instance_1;
    delete res_instance;
    delete resource;
    delete instance;
    delete object;

    free(m2mresourceinstance_stub::value);

    m2mresourceinstance_stub::clear();
    m2mresource_stub::clear();
    m2mobjectinstance_stub::clear();
    m2mobject_stub::clear();
}

void Test_M2MTLVSerializer::test_serialize_object_instance()
{
    M2MObject *object = new M2MObject("1", "1");
    M2MObjectInstance* instance = new M2MObjectInstance(*object,"1","type", "1");

    uint32_t size = 0;
    uint8_t *data = 0;
    m2mbase_stub::name_id_value = 0;
    M2MResource* resource = new M2MResource(*instance,
                                            "1",
                                            "type",
                                            M2MResourceInstance::STRING,
                                            false,
                                            "1");

    M2MResourceInstance* res_instance = new M2MResourceInstance(*resource,
                                                                "1",
                                                                "type",
                                                                M2MResourceInstance::STRING,
                                                                0,
                                                                "1",
                                                                false);

    m2mobjectinstance_stub::resource_list.clear();
    m2mobjectinstance_stub::resource_list.push_back(resource);

    m2mresource_stub::bool_value = true;
    m2mresource_stub::list.push_back(res_instance);

    m2mbase_stub::operation = M2MBase::GET_ALLOWED;

    data = serializer->serialize( m2mobjectinstance_stub::resource_list,size);
    CHECK(data != NULL);

    if(data) {
        free(data);
        data = NULL;
    }


    m2mbase_stub::name_id_value = -1;
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data == NULL);

    delete res_instance;
    delete resource;
    delete instance;
    delete object;

    m2mresource_stub::clear();
    m2mobjectinstance_stub::clear();
    m2mobject_stub::clear();
}

void Test_M2MTLVSerializer::test_serialize_resource()
{
    M2MObject *object = new M2MObject("1","1");
    M2MObjectInstance* instance =new M2MObjectInstance(*object,"1","type", "1");

    uint32_t size = 0;
    uint8_t *data = 0;
    m2mbase_stub::name_id_value = 0;
    M2MResource* resource = new M2MResource(*instance,
                                            "1",
                                            "type",
                                            M2MResourceInstance::INTEGER,
                                            false,
                                            "1");

    M2MResourceInstance* res_instance = new M2MResourceInstance(*resource,
                                                                "1",
                                                                "type",
                                                                M2MResourceInstance::INTEGER,
                                                                0,
                                                                "1",
                                                                false);


    m2mobjectinstance_stub::resource_list.clear();
    m2mobjectinstance_stub::resource_list.push_back(resource);

    m2mresource_stub::bool_value = true;
    m2mresource_stub::list.push_back(res_instance);

    m2mbase_stub::operation = M2MBase::GET_ALLOWED;

    data = serializer->serialize( resource,size);
    CHECK(data != NULL);

    if(data) {
        free(data);
        data = NULL;
    }

    m2mbase_stub::name_id_value = -1;
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data == NULL);

    delete res_instance;
    delete resource;
    delete instance;
    delete object;

    m2mresource_stub::clear();
    m2mobjectinstance_stub::clear();
    m2mobject_stub::clear();
}

void Test_M2MTLVSerializer::test_serialize_resource_instance()
{
    M2MObject *object = new M2MObject("1","1");
    M2MObjectInstance* instance = new M2MObjectInstance(*object,"1","type", "1");

    uint32_t size = 0;
    uint8_t *data = 0;
    m2mbase_stub::name_id_value = 0;
    M2MResource* resource = new M2MResource(*instance,
                                            "1",
                                            "type",
                                            M2MResourceInstance::INTEGER,
                                            false,
                                            "1");

    M2MResourceInstance* res_instance = new M2MResourceInstance(*resource,
                                                                "1",
                                                                "type",
                                                                M2MResourceInstance::INTEGER,
                                                                0,
                                                                "1",
                                                                false);


    m2mobjectinstance_stub::resource_list.clear();
    m2mobjectinstance_stub::resource_list.push_back(resource);

    m2mresource_stub::bool_value = true;
    m2mresource_stub::list.push_back(res_instance);

    m2mbase_stub::operation = M2MBase::GET_ALLOWED;

    data = serializer->serialize( m2mobjectinstance_stub::resource_list,size);
    CHECK(data != NULL);

    if(data) {
        free(data);
        data = NULL;
    }


    m2mbase_stub::name_id_value = -1;
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data == NULL);

    delete res_instance;
    delete resource;
    delete instance;
    delete object;

    m2mresource_stub::clear();
    m2mobjectinstance_stub::clear();
    m2mobject_stub::clear();
}

void Test_M2MTLVSerializer::test_serialize_resource_instance_out_of_memory()
{
    M2MObject *object = new M2MObject("1","1");
    M2MObjectInstance* instance = new M2MObjectInstance(*object,"1","type", "1");

    uint32_t size = 0;
    uint8_t *data = 0;
    m2mbase_stub::name_id_value = 0;
    M2MResource* resource = new M2MResource(*instance,
                                            "1",
                                            "type",
                                            M2MResourceInstance::INTEGER,
                                            false,
                                            "1");

    M2MResourceInstance* res_instance = new M2MResourceInstance(*resource,
                                                                "1",
                                                                "type",
                                                                M2MResourceInstance::INTEGER,
                                                                0,
                                                                "1",
                                                                false);


    m2mobjectinstance_stub::resource_list.clear();
    m2mobjectinstance_stub::resource_list.push_back(resource);

    m2mresource_stub::bool_value = true;
    m2mresource_stub::list.push_back(res_instance);

    m2mbase_stub::operation = M2MBase::GET_ALLOWED;
    memory_fail_counter=1; //apply for 1 time failing malloc
    memory_will_fail_counter=3; //after 3 successful ones
    data = serializer->serialize( m2mobjectinstance_stub::resource_list,size);
    CHECK(data == NULL);

    memory_fail_counter=1; //apply for 1 time failing malloc
    memory_will_fail_counter=4; //after 4 successful ones
    data = serializer->serialize( m2mobjectinstance_stub::resource_list,size);
    CHECK(data == NULL);

    m2mbase_stub::name_id_value = -1;
    data = serializer->serialize( m2mobject_stub::instance_list,size);
    CHECK(data == NULL);

    delete res_instance;
    delete resource;
    delete instance;
    delete object;

    m2mresource_stub::clear();
    m2mobjectinstance_stub::clear();
    m2mobject_stub::clear();
}
