#!/bin/bash

rm -f tests.out 2>&1 >/dev/null
for test in $(cat tests.in); do  
  echo "./a.out $test"
  ./a.out $test 2>&1 | tee -a tests.out
done

# following endian test taken from https://serverfault.com/questions/163487/how-to-tell-if-a-linux-system-is-big-endian-or-little-endian
littleEndian=$(echo -n I | hexdump -o | awk '{print substr($2,6,1); exit}')
if [[ $littleEndian == 0 ]]; then
  diff -iw tests.goldBE tests.out
  rc=$?
else
  diff -iw tests.goldLE tests.out
  rc=$?
fi

if [[ $rc == 0 ]]; then
  echo "All tests passed"
else
  echo "One or more tests failed"
fi
exit $rc
