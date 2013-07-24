#line 2 "test.ino"

// https://github.com/mmurdoch/arduinounit
#include <ArduinoUnit.h>
#include <DataStream.h>

test(instantiateInt) {
  // test int
  DataStream<int> s0 = DataStream<int>();
  assertEqual(0, s0.available());
  DataStream<int> s1 = DataStream<int>(1);
  assertEqual(0, s1.available());
  DataStream<int> s2 = DataStream<int>(2);
  assertEqual(0, s2.available());
  DataStream<int> s3 = DataStream<int>(3);
  assertEqual(0, s3.available());
  DataStream<int> s4 = DataStream<int>(100);
  assertEqual(0, s4.available());
  DataStream<int> s5 = DataStream<int>(1024);
  assertEqual(0, s5.available());
  DataStream<int> s6 = DataStream<int>(16536);
  assertEqual(0, s6.available());
  DataStream<int> s7 = DataStream<int>(65535);
  assertEqual(0, s7.available());
}

test(instantiateLong) {
  DataStream<long> s0 = DataStream<long>();
  assertEqual(0, s0.available());
  DataStream<long> s1 = DataStream<long>(1);
  assertEqual(0, s1.available());
  DataStream<long> s2 = DataStream<long>(2);
  assertEqual(0, s2.available());
  DataStream<long> s3 = DataStream<long>(3);
  assertEqual(0, s3.available());
  DataStream<long> s4 = DataStream<long>(100);
  assertEqual(0, s4.available());
  DataStream<long> s5 = DataStream<long>(1024);
  assertEqual(0, s5.available());
  DataStream<long> s6 = DataStream<long>(16536);
  assertEqual(0, s6.available());
  DataStream<long> s7 = DataStream<long>(65535);
  assertEqual(0, s7.available());
}

test(instantiateFloat) {
  DataStream<float> s0 = DataStream<float>();
  assertEqual(0, s0.available());
  DataStream<float> s1 = DataStream<float>(1);
  assertEqual(0, s1.available());
  DataStream<float> s2 = DataStream<float>(2);
  assertEqual(0, s2.available());
  DataStream<float> s3 = DataStream<float>(3);
  assertEqual(0, s3.available());
  DataStream<float> s4 = DataStream<float>(100);
  assertEqual(0, s4.available());
  DataStream<float> s5 = DataStream<float>(1024);
  assertEqual(0, s5.available());
  DataStream<float> s6 = DataStream<float>(16536);
  assertEqual(0, s6.available());
  DataStream<float> s7 = DataStream<float>(65535);
  assertEqual(0, s7.available());
}

test(writeInt) {
  DataStream<int> s0 = DataStream<int>(10);
  s0.write(145);
  assertEqual(1, s0.available());
  assertEqual(145, s0.read());
}

test(writeLong) {
  DataStream<long> s0 = DataStream<long>(10);
  s0.write(300000);
  assertEqual(1, s0.available());
  assertEqual(300000, s0.read());
}

test(writeFloat) {
  DataStream<float> s0 = DataStream<float>(10);
  s0.write(8.765);
  assertEqual(1, s0.available());
  assertEqual(8.765, s0.read());
}

test(available) {
  DataStream<long> s0 = DataStream<long>(3);
  assertEqual(0, s0.available());
}

test(read) {
    int data[3] = {1023,31000,99};
    DataStream<int> s = DataStream<int>(3, data, 3);
    
    assertEqual(3, s.available());
    assertEqual(1023, s.read());
    assertEqual(2, s.available());
    assertEqual(31000, s.read());
    assertEqual(1, s.available());
    assertEqual(99, s.read());
    assertEqual(0, s.available());

    // reading an empty buffer always returns -1
    //assertEqual(-1, s.read());
    //assertEqual(-1, s.read());
    //assertEqual(-1, s.read());    
}

/*
test(peek)
{
    int data[] = {1023,31000,99};
    DataStream s = DataStream(data, 3);
    
    assertEqual(3, s.available());
    assertEqual(1023, s.peek());
    assertEqual(1023, s.read());

    assertEqual(31000, s.peek());
    assertEqual(31000, s.read());
    
    assertEqual(1, s.available());
    assertEqual(99, s.peek());
    assertEqual(99, s.read());
    
    assertEqual(0, s.available());
    assertEqual(-1, s.peek());
    assertEqual(-1, s.read());
}
*/

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Test::run();
}
