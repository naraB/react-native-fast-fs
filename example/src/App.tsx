import React, { useCallback } from 'react';

import { StyleSheet, View, Text } from 'react-native';
import fs from 'react-native-fast-fs';
import RNFS from 'react-native-fs';

// const benchmarkReadDirectory = async () => {
//   // @ts-expect-error
//   // eslint-disable-next-line no-undef
//   const startTimeRNFS = performance.now();
//   await RNFS.readDir(RNFS.MainBundlePath);
//   // @ts-expect-error
//   // eslint-disable-next-line no-undef
//   const endTimeRNFS = performance.now();
//   const timeDiffRNFS = endTimeRNFS - startTimeRNFS;
//   // @ts-expect-error
//   // eslint-disable-next-line no-undef
//   const startTimeRNFFS = performance.now();
//   readDirectory(RNFS.MainBundlePath);
//   // @ts-expect-error
//   // eslint-disable-next-line no-undef
//   const endTimeRNFFS = performance.now();
//   const timeDiffRNFFS = endTimeRNFFS - startTimeRNFFS;
//   console.log(
//     'Benchmark results read directory: RNFS: ' +
//       timeDiffRNFS +
//       '\t RNFFS: ' +
//       timeDiffRNFFS
//   );
// };

// const benchmarkWriteFile = async () => {
//   let content = 'content';
//   for (let i = 0; i < 50; i++) {
//     content += 'Hello World ';
//   }

//   const pathSlow = RNFS.DocumentDirectoryPath + '/testSlow.txt';
//   const startTimeWriteSlow = performanceNow();
//   await RNFS.writeFile(pathSlow, content);
//   const endTimeWriteSlow = performanceNow();
//   const diffSlow = endTimeWriteSlow - startTimeWriteSlow;

//   const pathFast = RNFS.DocumentDirectoryPath + '/testFast.txt';
//   const startTimeWriteFast = performanceNow();
//   writeFile(pathFast, content);
//   const endTimeWriteFast = performanceNow();
//   const diffFast = endTimeWriteFast - startTimeWriteFast;

//   return [diffFast, diffSlow];
// };

// const benchmarkReadFile = async () => {
//   const pathFast = RNFS.DocumentDirectoryPath + '/testFast.txt';
//   const pathSlow = RNFS.DocumentDirectoryPath + '/testSlow.txt';

//   const startTimeWriteFast = performanceNow();
//   const fast1 = readFile(pathFast);
//   const endTimeWriteFast = performanceNow();
//   const diffFast = endTimeWriteFast - startTimeWriteFast;

//   const slow1 = readFile(pathSlow);

//   const startTimeWriteSlow = performanceNow();
//   const fast2 = await RNFS.readFile(pathFast);
//   const endTimeWriteSlow = performanceNow();
//   const diffSlow = endTimeWriteSlow - startTimeWriteSlow;

//   const slow2 = await RNFS.readFile(pathSlow);

//   if (fast1 !== fast2 || slow1 !== slow2) {
//     console.log('WORNG');
//   } else {
//     console.log('correct', fast1, +'\n' + fast2);
//   }

//   return [diffFast, diffSlow];

//   /*
//   const startTimeRNFFS = performanceNow();
//   const contentRNFFS =
//   const endTimeRNFFS = performanceNow();

//   let contentRNFS = '';
//   const startTimeRNFS = performanceNow();
//   try {
//     contentRNFS = await RNFS.readFile(path);
//   } catch (e) {
//     console.log(e);
//   }
//   const endTimeRNFS = performanceNow();
//   console.log(endTimeRNFS - startTimeRNFS, endTimeRNFFS - startTimeRNFFS);
//   if (contentRNFS !== contentRNFFS) {
//     console.log('mismatch: ', contentRNFFS, contentRNFS);
//   }
//   */
// };

export default function App() {
  const onPress = useCallback(async () => {
    //await benchmarkReadDirectory();
    //await benchmarkReadFile();
    /*
    const [timeFast, timeSlow] = await benchmarkWriteFile();
    console.log(`fast ${timeFast} - slow ${timeSlow}`);
    readDirectory()
    try {
      readFile(RNFS.DocumentDirectoryPath + '/testFast.txt');
    } catch (error) {
      console.log('COuld not deletel file', error);
    }
    */
    // const [fast, slow] = await benchmarkReadFile();
    // console.log(`fast ${fast} - slow ${slow}`);

    // try {
    //   fs.removeFile(path);
    // } catch (error) {
    //   console.error(error);
    // }

    // console.log('File at path: ', path);
    // console.log('File exists: ', fs.exists(path));
    // fs.writeFile(path, b64.repeat(10));
    // console.log('Content written: ', fs.exists(path));
    // console.log(
    //   'Read directory: ',
    //   fs.readDirectory(RNFS.DocumentDirectoryPath)
    // );

    //fs.writeFile(path, 'Hello');
    //fs.appendFile(path, ' World'.repeat(100));
    //console.log(fs.readFile(path));
    // console.log(fs.readdir(RNFS.DocumentDirectoryPath));
    // fs.mkdir(path);
    // const elements = fs.readdir(RNFS.DocumentDirectoryPath);

    // for (const element of elements) {
    //   fs.removeFile(RNFS.DocumentDirectoryPath + '/' + element);
    // }

    // fs.mkdir(RNFS.DocumentDirectoryPath + '/docs1' + '/docs2' + '/docs3', true);

    // console.log(fs.readdir(RNFS.DocumentDirectoryPath));
    // console.log(fs.readdir(RNFS.DocumentDirectoryPath + '/docs1'));
    // console.log(fs.readdir(RNFS.DocumentDirectoryPath + '/docs1' + '/docs2'));

    // const file = RNFS.DocumentDirectoryPath + 'helloWorld.txt';

    // fs.writeFile(file, 'Hello World');

    // const content = fs.readFile(file);

    // console.log(content);

    try {
      const path = '/storage/emulated/0/Android';

      await RNFS.writeFile(`${path}/helloWorld`, 'hello world');
      console.log(await RNFS.readDir(path));
      // console.log(fs.readFile(path));
      // const directoryContents = fs.readDir(path);

      // console.log(directoryContents, 'helo');

      // for (let dir of directoryContents) {
      //   console.log(dir);
      //   const permissions = fs.getPermissions(dir.path);
      //   console.log(dir.name, permissions.toString(2));
      // }
    } catch (e) {
      console.error(e);
    }

    // console.log(fs.rm(RNFS.DocumentDirectoryPath + '/docs1', true));

    // console.log(fs.readdir(RNFS.DocumentDirectoryPath));

    // console.log(await RNFS.read(path, 9, 0));

    // RNFS.writeFile(rnFilesystemFile, b64.repeat(10)).then(() =>
    //   console.log('I have written a smoll string :(')
    // );

    // console.log(
    //   'Is content read correctly: ',
    //   b64.repeat(10) === content && b64.repeat(10).length === content.length
    // );
    // fs.removeFile(path);
    // console.log('File exists: ', fs.exists(path));
    // fs.writeFile(path, 'HELLO WORLD 😊');
    // console.log(fs.readFileSync(path));
    // console.log(fs.readdirSync(RNFS.DocumentDirectoryPath));
    // fs.renameSync(path, RNFS.DocumentDirectoryPath + '/helloWorld.txt');
    // console.log(fs.readdirSync(RNFS.DocumentDirectoryPath));
    // console.log(fs.readdirSync(path));
    // fs.mkdirSync(path + '/docs');
    // console.log(fs.readdirSync(path));
    // fs.mkdirSync(path + '/docs1/docs2/docs3', true);
    // console.log(fs.readdirSync(path));
    // console.log(fs.readdirSync(path + '/docs1'));
    // console.log(fs.readdirSync(path + '/docs1/docs2'));
    //console.log(fs.mkdirSync(path + '/should/not/work'));
    // console.log(fs.readdirSync(path));
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
