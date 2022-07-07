const fs = require('fs');
const path = require('path');
const childProcess = require('child_process');

const TO_IGNORE = ['.git'];

function findCFiles(initialPath) {
  const files = [];
  const dirItems = fs.readdirSync(initialPath);
  for (const item of dirItems) {
    if (TO_IGNORE.includes(item)) continue;
    const fullPath = path.resolve(initialPath, item);
    if (fs.lstatSync(fullPath).isDirectory()) {
      files.push(...findCFiles(fullPath));
    } else if (path.extname(item) === '.c') {
      files.push(fullPath);
    }
  }
  return files;
}

console.log('Finding .c files...');
const cFiles = findCFiles(process.cwd());
console.log(`${cFiles.length} .c files found\n`);

for (const cFile of cFiles) {
  console.log(`Compiling ${cFile}`);
  try {
    const stdout = childProcess.execSync(`gcc -D TESTING -o ${process.cwd()}/exec ${cFile}`, { stdio: 'pipe' });
    console.log(stdout.toString());
  } catch (error) {
    console.log(error.message);
    break;
  }

  console.log(`Running ${cFile}`);
  try {
    const stdout = childProcess.execSync(`${process.cwd()}/exec`);
    console.log(stdout.toString());
  } catch (error) {
    console.log(error.message);
    break;
  }
}
