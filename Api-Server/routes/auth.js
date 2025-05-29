// 로그인 & 회원가입 라우터

const express = require('express');
const router = express.Router();
//const db = require('../db');
const crypto = require('crypto');

function hashPassword(password) {
    return crypto.createHash('sha256').update(password).digest('hex');
}

// 회원가입
router.post('/signup', async (req, res) => {
    const { userId, password, nickname } = req.body;

    try {
        const [rows] = await db.execute('SELECT * FROM users WHERE user_id = ?', [userId]);
        if (rows.length > 0) {
            return res.json({ success: false, error: '이미 존재하는 아이디입니다.' });
        }

        const passwordHash = hashPassword(password);
        await db.execute(
            'INSERT INTO users (user_id, password_hash, nickname) VALUES (?, ?, ?)',
            [userId, passwordHash, nickname]
        );

        res.json({ success: true });
    } catch (err) {
        console.error(err);
        res.json({ success: false, error: 'DB 오류' });
    }
});

// 로그인
router.post('/login', async (req, res) => {
const { userId, password } = req.body;

    try {
        const passwordHash = hashPassword(password);
        const [rows] = await db.execute(
            'SELECT id, nickname FROM users WHERE user_id = ? AND password_hash = ?',
            [userId, passwordHash]
        );

        if (rows.length === 0) {
            return res.json({ success: false, error: '아이디 또는 비밀번호 오류' });
        }

        const user = rows[0];
        res.json({
            success: true,
            playerId: user.id,
            nickname: user.nickname
        });
    } catch (err) {
        console.error(err);
        res.json({ success: false, error: 'DB 오류' });
    }
});

// 로그인
//router.post('/login', async (req, res) => {
//    const { userId, password } = req.body;
//    console.log(userId, password);
//
//    // 여기서 DB 체크 생략하고 무조건 성공으로 처리
//    if (userId === 'player1' && password === 'abc123') {
//        return res.json({
//            success: true,
//            userId : userId,
//            userNickname: 'user1',
//            playerID: 1
//        });
//    }
//
//    // 그 외는 실패 처리
//    res.json({ success: false, error: '아이디 또는 비밀번호 오류' });
//});


module.exports = router;