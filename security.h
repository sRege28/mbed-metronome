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
#ifndef __SECURITY_H__
#define __SECURITY_H__

#include <inttypes.h>

#define MBED_DOMAIN "43c75c7f-85a0-4488-84c9-82f88d98ec95"
#define MBED_ENDPOINT_NAME "147b4856-2553-4d17-bf51-72328d0130ab"

const uint8_t SERVER_CERT[] = "-----BEGIN CERTIFICATE-----\r\n"
"MIIBmDCCAT6gAwIBAgIEVUCA0jAKBggqhkjOPQQDAjBLMQswCQYDVQQGEwJGSTEN\r\n"
"MAsGA1UEBwwET3VsdTEMMAoGA1UECgwDQVJNMQwwCgYDVQQLDANJb1QxETAPBgNV\r\n"
"BAMMCEFSTSBtYmVkMB4XDTE1MDQyOTA2NTc0OFoXDTE4MDQyOTA2NTc0OFowSzEL\r\n"
"MAkGA1UEBhMCRkkxDTALBgNVBAcMBE91bHUxDDAKBgNVBAoMA0FSTTEMMAoGA1UE\r\n"
"CwwDSW9UMREwDwYDVQQDDAhBUk0gbWJlZDBZMBMGByqGSM49AgEGCCqGSM49AwEH\r\n"
"A0IABLuAyLSk0mA3awgFR5mw2RHth47tRUO44q/RdzFZnLsAsd18Esxd5LCpcT9w\r\n"
"0tvNfBv4xJxGw0wcYrPDDb8/rjujEDAOMAwGA1UdEwQFMAMBAf8wCgYIKoZIzj0E\r\n"
"AwIDSAAwRQIhAPAonEAkwixlJiyYRQQWpXtkMZax+VlEiS201BG0PpAzAiBh2RsD\r\n"
"NxLKWwf4O7D6JasGBYf9+ZLwl0iaRjTjytO+Kw==\r\n"
"-----END CERTIFICATE-----\r\n";

const uint8_t CERT[] = "-----BEGIN CERTIFICATE-----\r\n"
"MIIBzzCCAXOgAwIBAgIEJ2sUgzAMBggqhkjOPQQDAgUAMDkxCzAJBgNVBAYTAkZ\r\n"
"JMQwwCgYDVQQKDANBUk0xHDAaBgNVBAMME21iZWQtY29ubmVjdG9yLTIwMTgwHh\r\n"
"cNMTcwMjE4MjIwNjUyWhcNMTgxMjMxMDYwMDAwWjCBoTFSMFAGA1UEAxNJNDNjN\r\n"
"zVjN2YtODVhMC00NDg4LTg0YzktODJmODhkOThlYzk1LzE0N2I0ODU2LTI1NTMt\r\n"
"NGQxNy1iZjUxLTcyMzI4ZDAxMzBhYjEMMAoGA1UECxMDQVJNMRIwEAYDVQQKEwl\r\n"
"tYmVkIHVzZXIxDTALBgNVBAcTBE91bHUxDTALBgNVBAgTBE91bHUxCzAJBgNVBA\r\n"
"YTAkZJMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEbVyCpiZcmotzETPwf/Czz\r\n"
"abubCOWubgnY+MitJ/yqpcir1spu6FwlNyLx6B3JUDgKpTz7iD5GaThqzz/aiUw\r\n"
"djAMBggqhkjOPQQDAgUAA0gAMEUCIQC4xBx0uW4/vwyy8OFjj9zdHsFdkQVyWMw\r\n"
"2ym3NRIBeFAIgL+Hxyb1vDSq7j1mY03B9ohIodHjfpnRMrc7rPjqPqhM=\r\n"
"-----END CERTIFICATE-----\r\n";

const uint8_t KEY[] = "-----BEGIN PRIVATE KEY-----\r\n"
"MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgGneTYAhhOCSZPVsA\r\n"
"085A/CoYJPdqgTtnRTrDwkZt9IihRANCAARtXIKmJlyai3MRM/B/8LPNpu5sI5a5\r\n"
"uCdj4yK0n/KqlyKvWym7oXCU3IvHoHclQOAqlPPuIPkZpOGrPP9qJTB2\r\n"
"-----END PRIVATE KEY-----\r\n";

#endif //__SECURITY_H__