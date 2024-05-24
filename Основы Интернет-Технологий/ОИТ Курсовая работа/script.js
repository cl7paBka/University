// внешний файл со скриптами
function sendMessage(event) {
	event.preventDefault();

	// Получаем значения из формы
	const name = document.getElementById('name').value;
	const email = document.getElementById('email').value;
	const message = document.getElementById('message').value;

	// Отображаем сообщение
	alert(
		`Спасибо за ваше сообщение, ${name}!\nМы получили ваше письмо и ответим в ближайшее время.\n\nВаш email: ${email}\nВаше сообщение:\n${message}`,
	);

	// Очищаем поля формы
	document.getElementById('name').value = '';
	document.getElementById('email').value = '';
	document.getElementById('message').value = '';
}
