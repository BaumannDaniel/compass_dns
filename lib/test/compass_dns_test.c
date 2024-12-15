#include "unity.h"
#include "compass_dns.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void parse_dns_header__successfully() {
    const u_int8_t dns_header_bytes[12] = { 0x00, 0x05, 0x8f, 0xb3, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04 };
    const DnsHeader dns_header = parse_dns_header(dns_header_bytes);
    TEST_ASSERT_EQUAL(5, dns_header.id);
    TEST_ASSERT_EQUAL(1, dns_header.qr);
    TEST_ASSERT_EQUAL(1, dns_header.opcode);
    TEST_ASSERT_EQUAL(1, dns_header.aa);
    TEST_ASSERT_EQUAL(1, dns_header.tc);
    TEST_ASSERT_EQUAL(1, dns_header.rd);
    TEST_ASSERT_EQUAL(1, dns_header.ra);
    TEST_ASSERT_EQUAL(3, dns_header.z);
    TEST_ASSERT_EQUAL(3, dns_header.rcode);
    TEST_ASSERT_EQUAL(1, dns_header.qd_count);
    TEST_ASSERT_EQUAL(2, dns_header.an_count);
    TEST_ASSERT_EQUAL(3, dns_header.ns_count);
    TEST_ASSERT_EQUAL(4, dns_header.ar_count);
}

void dns_header_to_buffer__successfully() {
    const DnsHeader dns_header = {
        .id = 257,
        .qr = 1,
        .opcode = STATUS,
        .aa = 1,
        .tc = 1,
        .rd = 1,
        .ra = 1,
        .z = 1,
        .rcode = REFUSED,
        .qd_count = 4,
        .an_count = 3,
        .ns_count = 2,
        .ar_count = 1
    };
    u_int8_t buffer[12] = {0};
    dns_header_to_buffer(&dns_header, buffer);
    TEST_ASSERT_EQUAL(0x01, buffer[0]);
    TEST_ASSERT_EQUAL(0x01, buffer[1]);
    TEST_ASSERT_EQUAL(0x97, buffer[2]);
    TEST_ASSERT_EQUAL(0x95, buffer[3]);
    TEST_ASSERT_EQUAL(0x00, buffer[4]);
    TEST_ASSERT_EQUAL(0x04, buffer[5]);
    TEST_ASSERT_EQUAL(0x00, buffer[6]);
    TEST_ASSERT_EQUAL(0x03, buffer[7]);
    TEST_ASSERT_EQUAL(0x00, buffer[8]);
    TEST_ASSERT_EQUAL(0x02, buffer[9]);
    TEST_ASSERT_EQUAL(0x00, buffer[10]);
    TEST_ASSERT_EQUAL(0x01, buffer[11]);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(parse_dns_header__successfully);
    RUN_TEST(dns_header_to_buffer__successfully);
    return UNITY_END();
}