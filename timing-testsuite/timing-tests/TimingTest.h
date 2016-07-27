/* 
 * File:   TimingTest.h
 * Author: Juraj Somorovsky - juraj.somorovsky@hackmanit.de
 *
 * Created on July 6, 2016, 9:48 AM
 */

#ifndef TIMINGTEST_H
#define	TIMINGTEST_H

#include <botan/pubkey.h>
#include <botan/rsa.h>
#include <botan/system_rng.h>
#include <botan/hex.h>
#include <botan/rng.h>
#include <botan/numthry.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace Botan;

typedef unsigned long long ticks;


class TimingTest {
protected:
    std::string m_result_folder;
    std::vector<std::string> m_inputs;
    std::vector<ticks> m_results;
    unsigned int m_warmup_iterations = 500;
    unsigned int m_measurement_iterations = 10000;
    virtual std::vector<byte> prepare_input(std::string input) = 0;
    virtual ticks measure_critical_function(std::vector<byte> input) = 0;
    
    
public:
    TimingTest();
    virtual ~TimingTest();
    void execute_evaluation();
    void store_results_in_file(std::string file_name);
    ticks get_ticks();
};

class BleichenbacherTest : public TimingTest { 
private:
    const std::string m_encrypt_padding = "Raw";
    const std::string m_decrypt_padding = "PKCS1v15";
    const size_t m_expected_content_size = 48;
    const size_t m_ctext_length = 256;
    RSA_PrivateKey m_privkey;
    RSA_PublicKey m_pubkey;
    PK_Encryptor_EME m_enc;
    PK_Decryptor_EME m_dec;
    
protected:
    std::vector<byte> prepare_input(std::string input);
    ticks measure_critical_function(std::vector<byte> input);

public:
    BleichenbacherTest(std::vector<std::string> &inputs, std::string result_file, int keysize);
};


#endif	/* TIMINGTEST_H */

