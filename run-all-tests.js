const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

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
const allFiles = findCFiles(process.cwd());
console.log(`${allFiles.length} .c files found\n`);

const sortedFiles = orderFileByLastModified();

for (const cFile of sortedFiles) {
  const shortFilename = cFile.replace(process.cwd(), '');
  console.log(`*** Compiling ${shortFilename}`);
  try {
    execSync(`./run ${cFile}`, { stdio: 'inherit' });
  } catch (error) {
    console.log(error.message);
    break;
  }

  console.log(`>>> Running ${shortFilename}`);
  try {
    execSync(`${process.cwd()}/exec`, { stdio: 'inherit' });
  } catch (error) {
    console.log(error.message);
    break;
  }

  console.log('\n');
}

function orderFileByLastModified() {
  const filesStats = createFilesStats();
  return allFiles.sort((fileA, fileB) => {
    return filesStats[fileB].mtime.getTime() - filesStats[fileA].mtime.getTime();
  });
}

function createFilesStats() {
  const result = {};
  for (const file of allFiles) {
    const stat = fs.statSync(file);
    result[file] = stat;
  }
  return result;
}
