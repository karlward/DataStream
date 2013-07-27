// See https://github.com/mmurdoch/arduinounit
#include <ArduinoUnit.h>
// See https://github.com/karlward/DataStream
#include <DataStream.h>

test(instantiateInt) {
  DataStream<int> s0 = DataStream<int>();
  assertEqual(0, s0.available());
  DataStream<int> s1 = DataStream<int>(1);
  assertEqual(0, s1.available());
  DataStream<int> s2 = DataStream<int>(2);
  assertEqual(0, s2.available());
  DataStream<int> s3 = DataStream<int>(3);
  assertEqual(0, s3.available());
  DataStream<int> s4 = DataStream<int>(1024);
  assertEqual(0, s4.available());
  DataStream<int> s5 = DataStream<int>(65535);
  assertEqual(0, s5.available());
  DataStream<int> s6 = DataStream<int>(4294967295);
  assertEqual(0, s6.available());
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
  DataStream<long> s4 = DataStream<long>(1024);
  assertEqual(0, s4.available());
  DataStream<long> s5 = DataStream<long>(65535);
  assertEqual(0, s5.available());
  DataStream<long> s6 = DataStream<long>(4294967295);
  assertEqual(0, s6.available());
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
  DataStream<float> s4 = DataStream<float>(1024);
  assertEqual(0, s4.available());
  DataStream<float> s5 = DataStream<float>(65535);
  assertEqual(0, s5.available());
  DataStream<float> s6 = DataStream<float>(4294967295);
  assertEqual(0, s6.available());
}

test(writeInt) {
  DataStream<int> s0 = DataStream<int>(10);
  s0.write(145);
  assertEqual(1, s0.available());
  assertEqual(145, s0.read());
  for (int i = 0; i < 100; i++) { 
    s0.write(i); 
  }
  for (int j = 90; j < 100; j++) { 
    assertEqual((100 - j), s0.available());
    assertEqual(j, s0.read());
  }
}

test(writeLong) {
  DataStream<long> s0 = DataStream<long>(10);
  s0.write(300000);
  assertEqual(1, s0.available());
  assertEqual(300000, s0.read());
  s0.write(4294967295); 
  assertEqual(1, s0.available());
  assertEqual(4294967295, s0.read());
  for (long i = 0; i < 100; i++) { 
    s0.write(i); 
  }
  for (long j = 90; j < 100; j++) { 
    assertEqual((100 - j), s0.available());
    assertEqual(j, s0.read());
  }
}

test(writeFloat) {
  DataStream<float> s0 = DataStream<float>(10);
  s0.write(8.765);
  assertEqual(1, s0.available());
  assertEqual(8.765, s0.read());
  for (float i = 0.0; i < 100.0; i++) { 
    s0.write(i); 
  }
  for (long j = 90.0; j < 100.0; j++) { 
    assertEqual((100.0 - j), s0.available());
    assertEqual(j, s0.read());
  }
}

test(available) {
  DataStream<int> s0 = DataStream<int>(3);
  assertEqual(0, s0.available());
  assertEqual(0, s0.available());
  s0.write(18);
  assertEqual(1, s0.available());
  assertEqual(1, s0.available());
  s0.write(1790);
  assertEqual(2, s0.available());
  assertEqual(2, s0.available());
  s0.write(17648);
  assertEqual(3, s0.available());
  assertEqual(3, s0.available());
  s0.write(24);
  assertEqual(3, s0.available());
  assertEqual(3, s0.available());
  s0.write(2478);
  assertEqual(3, s0.available());
  assertEqual(3, s0.available());
  assertEqual(3, s0.available());

  DataStream<long> s1 = DataStream<long>(3);
  assertEqual(0, s1.available());
  assertEqual(0, s1.available());
  s1.write(1800);
  assertEqual(1, s1.available());
  assertEqual(1, s1.available());
  s1.write(179000);
  assertEqual(2, s1.available());
  assertEqual(2, s1.available());
  s1.write(1764800);
  assertEqual(3, s1.available());
  assertEqual(3, s1.available());
  s1.write(4200000000);
  assertEqual(3, s1.available());
  assertEqual(3, s1.available());
  s1.write(247800);
  assertEqual(3, s1.available());
  assertEqual(3, s1.available());

  DataStream<float> s2 = DataStream<float>(3);
  assertEqual(0, s2.available());
  assertEqual(0, s2.available());
  s2.write(18.45787);
  assertEqual(1, s2.available());
  assertEqual(1, s2.available());
  s2.write(1790.789645);
  assertEqual(2, s2.available());
  assertEqual(2, s2.available());
  s2.write(17648.6754);
  assertEqual(3, s2.available());
  assertEqual(3, s2.available());
  s2.write(24.01);
  assertEqual(3, s2.available());
  assertEqual(3, s2.available());
  s2.write(2478.68764);
  assertEqual(3, s2.available());
  assertEqual(3, s2.available());
}

test(readInt) {
  int data[3] = {1023, 31000, 99};
  DataStream<int> s = DataStream<int>(3, data, 3);
  
  assertEqual(3, s.available());
  assertEqual(1023, s.read());
  assertEqual(2, s.available());
  assertEqual(31000, s.read());
  assertEqual(1, s.available());
  assertEqual(99, s.read());
  assertEqual(0, s.available());
}

test(readLong) {
  long data[5] = {101500, 32, 9, 4200000000, 0};
  DataStream<long> s = DataStream<long>(5, data, 5);
  
  assertEqual(5, s.available());
  assertEqual(101500, s.read());
  assertEqual(4, s.available());
  assertEqual(32, s.read());
  assertEqual(3, s.available());
  assertEqual(9, s.read());
  assertEqual(2, s.available());
  assertEqual(4200000000, s.read());
  assertEqual(1, s.available());
  assertEqual(0, s.read());
  assertEqual(0, s.available());
}

test(peekInt) {
  int data[3] = {1023,31000,99};
  DataStream<int> s = DataStream<int>(3, data, 3);
  
  assertEqual(3, s.available());
  assertEqual(1023, s.peek());
  assertEqual(1023, s.read());

  assertEqual(31000, s.peek());
  assertEqual(31000, s.read());
  
  assertEqual(1, s.available());
  assertEqual(99, s.peek());
  assertEqual(99, s.read());
  
  assertEqual(0, s.available());
}

test(flushInt) {
  int data[3] = {1023,31000,99};
  DataStream<int> s = DataStream<int>(3, data, 3);
  s.flush();
  assertEqual(0, s.available());
} 

test(flushLong) {
  long data[3] = {1023,3100000000,99};
  DataStream<long> s = DataStream<long>(3, data, 3);
  s.flush();
  assertEqual(0, s.available());
} 

test(flushFloat) {
  float data[3] = {1023.5,31000.11,99.08};
  DataStream<float> s = DataStream<float>(3, data, 3);
  s.flush();
  assertEqual(0, s.available());
} 

test(resize) {
  int data[3] = {1023,31000,99};
  DataStream<int> s = DataStream<int>(3, data, 3);
  assertEqual(3, s.available());
  s.resize(4);
  s.write(100);
  assertEqual(4, s.available());
  s.resize(5);
  s.write(4568);
  assertEqual(5, s.available());
  s.resize(4);
  assertEqual(4, s.available());
  s.resize(1);
  assertEqual(1, s.available());
}

test(writeOrdered) {
  int data[6] = {1023,31000,99,0,18,-32};
  DataStream<int> s = DataStream<int>(6);
  for (int i=0; i<6; i++) {
    s.writeOrdered(data[i]);
  }
  assertEqual(-32, s.read());
  assertEqual(0, s.read());
  assertEqual(18, s.read());
  assertEqual(99, s.read());
  assertEqual(1023, s.read());
  assertEqual(31000, s.read());
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}
