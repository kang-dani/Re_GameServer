const express = require('express');
const passport = require('passport');

const router = express.Router();

router.get('/google', passport.authenticate('google', {
    scope: ['profile', 'email']
}));

router.get('/google/callback',
    passport.authenticate('google', { failureRedirect: '/api/google/login' }),
    (req, res) => {
        res.redirect('/api/google/success');
    }
);

router.get('/google/success', (req, res) => {
    res.send(`로그인 성공: ${req.user.displayName}`);
});

router.get('/google/login', (req, res) => {
    res.send('로그인 실패');
});

module.exports = router;