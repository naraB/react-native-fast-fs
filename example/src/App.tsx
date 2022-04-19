import React, { useCallback } from 'react';

import { StyleSheet, View, Text } from 'react-native';
import { readDirectory, readFile, writeFile } from 'react-native-fast-fs';
import RNFS from 'react-native-fs';
import { b64 } from './test';

// @ts-expect-error
// eslint-disable-next-line no-undef
const performanceNow = () => performance.now();

const benchmarkReadDirectory = async () => {
  // @ts-expect-error
  // eslint-disable-next-line no-undef
  const startTimeRNFS = performance.now();
  await RNFS.readDir(RNFS.MainBundlePath);
  // @ts-expect-error
  // eslint-disable-next-line no-undef
  const endTimeRNFS = performance.now();
  const timeDiffRNFS = endTimeRNFS - startTimeRNFS;
  // @ts-expect-error
  // eslint-disable-next-line no-undef
  const startTimeRNFFS = performance.now();
  readDirectory(RNFS.MainBundlePath);
  // @ts-expect-error
  // eslint-disable-next-line no-undef
  const endTimeRNFFS = performance.now();
  const timeDiffRNFFS = endTimeRNFFS - startTimeRNFFS;
  console.log(
    'Benchmark results read directory: RNFS: ' +
      timeDiffRNFS +
      '\t RNFFS: ' +
      timeDiffRNFFS
  );
};

const benchmarkWriteFile = async () => {
  let content = 'content';
  for (let i = 0; i < 50; i++) {
    content += 'Hello World ';
  }

  const pathSlow = RNFS.DocumentDirectoryPath + '/testSlow.txt';
  const startTimeWriteSlow = performanceNow();
  await RNFS.writeFile(pathSlow, content);
  const endTimeWriteSlow = performanceNow();
  const diffSlow = endTimeWriteSlow - startTimeWriteSlow;

  const pathFast = RNFS.DocumentDirectoryPath + '/testFast.txt';
  const startTimeWriteFast = performanceNow();
  writeFile(pathFast, content);
  const endTimeWriteFast = performanceNow();
  const diffFast = endTimeWriteFast - startTimeWriteFast;

  return [diffFast, diffSlow];
};

const benchmarkReadFile = async () => {
  const pathFast = RNFS.DocumentDirectoryPath + '/testFast.txt';
  const pathSlow = RNFS.DocumentDirectoryPath + '/testSlow.txt';

  const startTimeWriteFast = performanceNow();
  const fast1 = readFile(pathFast);
  const endTimeWriteFast = performanceNow();
  const diffFast = endTimeWriteFast - startTimeWriteFast;

  const slow1 = readFile(pathSlow);

  const startTimeWriteSlow = performanceNow();
  const fast2 = await RNFS.readFile(pathFast);
  const endTimeWriteSlow = performanceNow();
  const diffSlow = endTimeWriteSlow - startTimeWriteSlow;

  const slow2 = await RNFS.readFile(pathSlow);

  if (fast1 !== fast2 || slow1 !== slow2) {
    console.log('WORNG');
  } else {
    console.log('correct', fast1, +'\n' + fast2);
  }

  return [diffFast, diffSlow];

  /*
  const startTimeRNFFS = performanceNow();
  const contentRNFFS = 
  const endTimeRNFFS = performanceNow();

  let contentRNFS = '';
  const startTimeRNFS = performanceNow();
  try {
    contentRNFS = await RNFS.readFile(path);
  } catch (e) {
    console.log(e);
  }
  const endTimeRNFS = performanceNow();
  console.log(endTimeRNFS - startTimeRNFS, endTimeRNFFS - startTimeRNFFS);
  if (contentRNFS !== contentRNFFS) {
    console.log('mismatch: ', contentRNFFS, contentRNFS);
  }
  */
};

export default function App() {
  const onPress = useCallback(async () => {
    //await benchmarkReadDirectory();
    //await benchmarkReadFile();
    const [timeFast, timeSlow] = await benchmarkWriteFile();
    console.log(`fast ${timeFast} - slow ${timeSlow}`);
    const [fast, slow] = await benchmarkReadFile();
    console.log(`fast ${fast} - slow ${slow}`);
  }, []);

  return (
    <View style={styles.container}>
      <Text onPress={onPress}>Press me to see some speed!</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
