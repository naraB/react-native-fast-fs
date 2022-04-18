import React, { useEffect } from 'react';

import { StyleSheet, View, Text } from 'react-native';
import { readDir } from 'react-native-fast-fs';
import RNFS from 'react-native-fs';

export default function App() {
  useEffect(() => {
    // @ts-expect-error
    // eslint-disable-next-line no-undef
    const startTime = performance.now();
    const files = readDir(RNFS.MainBundlePath);
    // @ts-expect-error
    // eslint-disable-next-line no-undef
    const endTime = performance.now();
    const timeDiff = endTime - startTime;
    console.log(timeDiff + ' ms');
    console.log(files);
  }, []);

  return (
    <View style={styles.container}>
      <Text>Result: {'hello'}</Text>
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
