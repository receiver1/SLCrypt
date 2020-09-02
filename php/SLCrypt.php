<?php
	class SLCrypt {
		function toByteArray($hex)
		{
			$arr = [];
			for ($i = 0; $i < strlen($hex); $i+=2) {
				array_push($arr, $hex[$i] . $hex[$i + 1]);
			}
			return $arr;
		}
		
		function generateInitVector()
		{
			$out = "";
			mt_srand(microtime(true));
			for ($i = 0; $i < $this->blockBytesLen; $i++) {
				$out .= chr(mt_rand(ord('a'), ord('z')));
			}
			return $out;
		}
		
		function encryptString($in, $key)
		{
			$iv = $this->toByteArray(bin2hex($this->generateInitVector()));
			$in = $this->toByteArray(bin2hex($in));
			$key = $this->toByteArray(bin2hex($key));
			
			$encryptedBytes = "";
			$paddingLength = ceil(sizeof($in) / $this->blockBytesLen);
			for ($a = 0; $a <= $paddingLength; $a++) {
				for ($b = 0; $b < $this->blockBytesLen; $b++) {
					if (sizeof($in) > $a * $this->blockBytesLen + $b) {
						$first = hexdec($in[$a * $this->blockBytesLen + $b]);	
						$second = hexdec($iv[$b]);
						$third = hexdec($key[$b]);
						$encryptedBytes .= dechex($first + $second - $third);
					}
				}
			}
			return hex2bin(implode('', $iv) . "$encryptedBytes");
		}
		
		function decryptString($in, $key)
		{
			$iv = substr($in, 0, 16);
			$in = substr($in, 16);
			
			$iv = $this->toByteArray(bin2hex($iv));
			$in = $this->toByteArray(bin2hex($in));
			$key = $this->toByteArray(bin2hex($key));
			
			$decryptedBytes = "";
			$paddingLength = ceil(sizeof($in) / $this->blockBytesLen);
			for ($a = 0; $a <= $paddingLength; $a++) {
				for ($b = 0; $b < $this->blockBytesLen; $b++) {
					if (sizeof($in) > $a * $this->blockBytesLen + $b) {
						if (hexdec($in[$a * $this->blockBytesLen + $b]) != 0x00) {
							$first = hexdec($in[$a * $this->blockBytesLen + $b]);	
							$second = hexdec($iv[$b]);
							$third = hexdec($key[$b]);
							$decryptedBytes .= dechex($first - $second + $third);
						}
					}
				}
			}
			return hex2bin("$decryptedBytes");
		}
		
		private $blockBytesLen = 16;
	};
?>
