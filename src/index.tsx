import { NativeModules, Platform } from 'react-native';

const LINKING_ERROR =
  `The package 'react-native-fast-fs' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo managed workflow\n';

const FastFs = NativeModules.FastFs;

FastFs.install();

if (FastFs == null) {
  throw new Error(LINKING_ERROR);
}

export enum Encoding {
  Base64 = 'base64',
  Utf8 = 'utf8',
}

export type File = {
  size: number;
  isFile: boolean;
  isDirectory: boolean;
  name: string;
  path: string;
  lastModified: string; // TODO: Construct date object via .callFromConstructor?
  created: string;
};

function readDir(path: string): File[] {
  // @ts-expect-error I inject that function using JSI.
  return global.readDir(path);
}

function readdir(path: string): string[] {
  // @ts-expect-error I inject that function using JSI.
  return global.readdir(path);
}

function mkdir(path: string, recursive: boolean = false): string[] {
  // @ts-expect-error I inject that function using JSI.
  return global.mkdir(path, recursive);
}

function moveFile(oldPath: string, newPath: string): void {
  // @ts-expect-error I inject that function using JSI.
  return global.moveFile(oldPath, newPath);
}

function read(path: string, start: number, end: number): string {
  // @ts-expect-error I inject that function using JSI.
  return global.read(path, start, end);
}

/**
 * Synchronously reads file at provided path.
 *
 * Throws exception
 *  - If path does not point to a file
 *  - If file at path does not exist
 *  - If you don't have read permissions on the file
 * @param path
 * @param encoding (default UTF8) specifies with which encoding the content of the file should be read
 * @returns a string encoded with the specified encoding
 */
function readFile(
  path: string,
  // @ts-expect-error
  encoding?: Encoding = Encoding.Utf8
): string {
  // @ts-expect-error I inject that function using JSI.
  return global.readFile(path, encoding);
}

function readFileAsync(
  path: string,
  // @ts-expect-error
  encoding?: Encoding = Encoding.Utf8
): Promise<string> {
  // @ts-expect-error I inject that function using JSI.
  return global.readFileAsync(path, encoding);
}

function writeFile(path: string, content: string): void {
  // @ts-expect-error I inject that function using JSI.
  return global.writeFile(path, content);
}

function writeFileAsync(path: string, content: string): Promise<void> {
  // @ts-expect-error I inject that function using JSI.
  return global.writeFileAsync(path, content);
}

function appendFile(path: string, content: string): void {
  // @ts-expect-error I inject that function using JSI.
  return global.appendFile(path, content);
}

function rm(path: string, recursive: boolean = false): boolean {
  // @ts-expect-error I inject that function using JSI.
  return global.rm(path, recursive);
}
function copyFile(sourcePath: string, targetPath: string): void {
  // @ts-expect-error I inject that function using JSI.
  return global.copyFile(sourcePath, targetPath);
}

function exists(path: string): boolean {
  // @ts-expect-error I inject that function using JSI.
  return global.exists(path);
}
function getPermissions(path: string): number {
  // @ts-expect-error I inject that function using JSI.
  return global.getPermissions(path);
}

const fs = {
  rm,
  readFile,
  readFileAsync,
  writeFile,
  writeFileAsync,
  appendFile,
  exists,
  copyFile,
  readDir,
  readdir,
  mkdir,
  moveFile,
  read,
  getPermissions,
};

export default fs;
