const { Router } = require("express")

const router = Router()

router.get("/", (req, res) => {
    res.status(200).json({ message: "Estoy en Usuario" })
});

module.exports = router;