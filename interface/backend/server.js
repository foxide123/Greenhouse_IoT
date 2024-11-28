const express = require('express');
const path = require('path')
const { exec } = require('child_process');
const app = express();
const cors = require('cors');
const port = 3001;

app.use(cors());

app.use(express.static(path.join(__dirname, '../web_frontend')));

app.use(express.json());

app.get('/get_data', (req, res) => {
  exec('./greenhouse', (error, stdout, stderr) => {
    if (error) {
      console.error(`Execution error: ${error.message}`);
      return res.status(500).send(`Server Error: ${error.message}`);
    }
    if (stderr) {
      console.error(`Stderr: ${stderr}`);
      return res.status(500).send(`Server Error: ${stderr.message}`);
    }
    
    let data;
    try{
      data = JSON.parse(stdout);
      console.log(data);
    }catch(parseError){
      return res.status(500).send(`Server Error (parseError): ${parseError.message}`);
    }

    res.json(data);
  });
});

app.listen(port, () => {
  console.log(`Backend server running at http://localhost:${port}`);
});
