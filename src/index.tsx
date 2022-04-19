import { NativeModules, Platform } from 'react-native';

const LINKING_ERROR =
  `The package 'react-native-fast-fs' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo managed workflow\n';

const fs = NativeModules.FastFs;

fs.install();

if (fs == null) {
  throw new Error(LINKING_ERROR);
}

export type File = {
  size: number;
  isFile: boolean;
  isDirectory: boolean;
  name: string;
  path: string;
};

export function readDirectory(path: string): File[] {
  // @ts-expect-error I inject that function using JSI.
  return global.__readDirectory(path);
}

export function readFile(path: string): string {
  // @ts-expect-error I inject that function using JSI.
  return global.__readFile(path);
}

export function writeFile(path: string, content: string): boolean {
  // @ts-expect-error I inject that function using JSI.
  return global.__writeFile(path, content);
}
