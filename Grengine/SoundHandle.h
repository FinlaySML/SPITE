#pragma once
namespace Spite {
	/// <summary>
	/// A non-owning handle for a sample/stream instance
	/// </summary>
	struct SoundHandle {
		std::uint64_t underlying;
		/// <summary>
		/// Set the volume of the the instance that this handle points to
		/// </summary>
		/// <param name="multiplier">The volume; 0..1</param>
		/// <returns></returns>
		SoundHandle Volume(float multiplier);
		/// <summary>
		/// Set the speed of the the instance that this handle points to
		/// </summary>
		/// <param name="multiplier">The speed</param>
		/// <returns></returns>
		SoundHandle Speed(float multiplier);
		/// <summary>
		/// Delay the sound by some amount of seconds.
		/// <para>Do not call this if the sound has already started playing</para>
		/// </summary>
		/// <param name="seconds"></param>
		/// <returns></returns>
		SoundHandle Delay(float seconds);
		/// <summary>
		/// Play or pause the sound
		/// </summary>
		/// <param name="isPlaying">True = Play; False = Pause</param>
		/// <returns></returns>
		SoundHandle PlayOrPause(bool isPlaying);
		/// <summary>
		/// Play the sound
		/// </summary>
		/// <returns></returns>
		SoundHandle Play();
		/// <summary>
		/// Pause the sound
		/// </summary>
		/// <returns></returns>
		SoundHandle Pause();
		/// <summary>
		/// Set wether the sound should loop when it gets to the end
		/// </summary>
		/// <returns></returns>
		SoundHandle Loop(bool looping = true);
		/// <summary>
		/// Go to a (absolute) point in time in the sound,  
		/// </summary>
		/// <param name="seconds"></param>
		/// <returns></returns>
		SoundHandle Seek(float seconds);
	};
}
