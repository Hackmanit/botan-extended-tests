/* 
 * File:   Lucky13Test.cpp
 * Author: Juraj Somorovsky - juraj.somorovsky@hackmanit.de
 * 
 * Created on September 9, 2016
 */

#include "TimingTest.h"

Lucky13Test::Lucky13Test(std::vector<std::string> &inputs, std::string result_folder) {
    m_inputs = inputs;
    m_result_folder = result_folder;
    m_warmup_iterations = 0;
    m_measurement_iterations = 1;


}

std::vector<byte> Lucky13Test::prepare_input(std::string input) {
    const std::vector<uint8_t> input_vector = Botan::hex_decode(input);
    return input_vector;
}

ticks Lucky13Test::measure_critical_function(std::vector<byte> input) {
    const Botan::byte* in = &input[0];


    secure_vector<byte> record_data;
    u64bit record_sequence = 0;
    TLS::Record_Type record_type = TLS::NO_RECORD;
    TLS::Protocol_Version record_version;

    size_t consumed = 0;

    // RSA_WITH_AES_256_CBC_SHA
    TLS::Ciphersuite cs = TLS::Ciphersuite::by_id(0x0035);
    TLS::Session_Keys sk;
//    TLS::Connection_Cipher_State state(TLS::Protocol_Version::TLS_V12, TLS::Connection_Side::SERVER, true, cs, sk, false);
    TLS::Connection_Cipher_State state;


//        TLS::Record_Raw_Input raw_input(input, 10, consumed, false);
//        TLS::Record record(record_data, &record_sequence, &record_version, &record_type);
    //    const size_t needed =
    //            read_record(m_readbuf,
    //            raw_input,
    //            record,
    //            m_sequence_numbers.get(),
    //            std::bind(&TLS::Channel::read_cipher_state_epoch, this,
    //            std::placeholders::_1));


    ticks start = this->get_ticks();
    ticks end = get_ticks();

    return (end - start);
}

