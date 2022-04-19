import React, { useCallback } from 'react';

import { StyleSheet, View, Text } from 'react-native';
import { readDirectory, readFile } from 'react-native-fast-fs';
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

const benchmarkReadFile = async () => {
  const path = RNFS.DocumentDirectoryPath + '/test.txt';

  const res = await RNFS.writeFile(
    path,
    b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64 +
      b64
  );
  console.log(res);

  const startTimeRNFFS = performanceNow();
  const contentRNFFS = readFile(path);
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
};

export default function App() {
  const onPress = useCallback(async () => {
    await benchmarkReadDirectory();
    await benchmarkReadFile();
    // for (const file of files) {
    //   if (file.isFile) {
    //     console.log('reading file: ', file.path);
    //     const content = readFile(file.path);
    //     console.log('Hello', content);
    //   }
    // }
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
