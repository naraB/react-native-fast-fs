export type File = {
  size: number;
  isFile: boolean;
  isDirectory: boolean;
  name: string;
  path: string;
};

declare function __readDirectory(a: string): File[];

export function readDirectory(a: string): File[] {
  return __readDirectory(a);
}

declare function __readFile(path: string): string;

export function readFile(path: string): string {
  return __readFile(path);
}
