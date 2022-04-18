type File = {
  size: number;
  isFile: boolean;
  isDirectory: boolean;
  name: string;
  path: string;
};

declare function readDirectory(a: string): File[];

export function readDir(a: string): File[] {
  return readDirectory(a);
}
