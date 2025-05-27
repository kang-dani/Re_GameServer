const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');

const app = express();

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// 또는 최신 express에선 이거 하나로도 됨
// app.use(express.json());

app.use('/api', require('./routes/auth')); // 경로 라우터 등록

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`API Server running on http://localhost:${PORT}`);
});
